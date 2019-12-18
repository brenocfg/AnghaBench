#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct iser_device {int comps_used; struct iser_comp* comps; TYPE_2__* pd; int /*<<< orphan*/  event_handler; struct ib_device* ib_device; TYPE_2__* mr; } ;
struct iser_comp {TYPE_2__* cq; scalar_t__ tq; int /*<<< orphan*/  task; struct iser_device* device; } ;
struct TYPE_8__ {int device_cap_flags; int /*<<< orphan*/  max_cqe; } ;
struct ib_device {int /*<<< orphan*/  num_comp_vectors; int /*<<< orphan*/  name; TYPE_1__ attrs; } ;
struct ib_cq_init_attr {int cqe; int comp_vector; } ;
struct TYPE_9__ {struct TYPE_9__* __internal_mr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_CQ_NEXT_COMP ; 
 int IB_DEVICE_MEM_MGT_EXTENSIONS ; 
 int /*<<< orphan*/  IB_PD_UNSAFE_GLOBAL_RKEY ; 
 int /*<<< orphan*/  INIT_IB_EVENT_HANDLER (int /*<<< orphan*/ *,struct ib_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISER_DBG (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ISER_ERR (char*,...) ; 
 int /*<<< orphan*/  ISER_MAX_CQ_LEN ; 
 scalar_t__ IS_ERR (TYPE_2__*) ; 
 int /*<<< orphan*/  M_ISER_VERBS ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PI_NET ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iser_comp*) ; 
 int /*<<< orphan*/  free (struct iser_comp*,int /*<<< orphan*/ ) ; 
 TYPE_2__* ib_alloc_pd (struct ib_device*,int /*<<< orphan*/ ) ; 
 TYPE_2__* ib_create_cq (struct ib_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,struct ib_cq_init_attr*) ; 
 int /*<<< orphan*/  ib_dealloc_pd (TYPE_2__*) ; 
 int /*<<< orphan*/  ib_destroy_cq (TYPE_2__*) ; 
 scalar_t__ ib_register_event_handler (int /*<<< orphan*/ *) ; 
 scalar_t__ ib_req_notify_cq (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iser_cq_callback ; 
 int /*<<< orphan*/  iser_cq_event_callback ; 
 int /*<<< orphan*/  iser_cq_tasklet_fn ; 
 int /*<<< orphan*/  iser_event_handler ; 
 struct iser_comp* malloc (int,int /*<<< orphan*/ ,int) ; 
 void* min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_ncpus ; 
 scalar_t__ taskqueue_create_fast (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  taskqueue_free (scalar_t__) ; 
 int /*<<< orphan*/  taskqueue_start_threads (scalar_t__*,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  taskqueue_thread_enqueue ; 

__attribute__((used)) static int
iser_create_device_ib_res(struct iser_device *device)
{
	struct ib_device *ib_dev = device->ib_device;
	int i, max_cqe;

	if (!(ib_dev->attrs.device_cap_flags & IB_DEVICE_MEM_MGT_EXTENSIONS)) {
		ISER_ERR("device %s doesn't support Fastreg, "
			 "can't register memory", device->ib_device->name);
		return (1);
	}

	device->comps_used = min(mp_ncpus, device->ib_device->num_comp_vectors);

	device->comps = malloc(device->comps_used * sizeof(*device->comps),
		M_ISER_VERBS, M_WAITOK | M_ZERO);
	if (!device->comps)
		goto comps_err;

	max_cqe = min(ISER_MAX_CQ_LEN, ib_dev->attrs.max_cqe);

	ISER_DBG("using %d CQs, device %s supports %d vectors max_cqe %d",
		 device->comps_used, device->ib_device->name,
		 device->ib_device->num_comp_vectors, max_cqe);

	device->pd = ib_alloc_pd(device->ib_device, IB_PD_UNSAFE_GLOBAL_RKEY);
	if (IS_ERR(device->pd))
		goto pd_err;

	for (i = 0; i < device->comps_used; i++) {
		struct iser_comp *comp = &device->comps[i];
		struct ib_cq_init_attr cq_attr = {
			.cqe		= max_cqe,
			.comp_vector	= i,
		};

		comp->device = device;
		comp->cq = ib_create_cq(device->ib_device,
					iser_cq_callback,
					iser_cq_event_callback,
					(void *)comp,
					&cq_attr);
		if (IS_ERR(comp->cq)) {
			comp->cq = NULL;
			goto cq_err;
		}

		if (ib_req_notify_cq(comp->cq, IB_CQ_NEXT_COMP))
			goto cq_err;

		TASK_INIT(&comp->task, 0, iser_cq_tasklet_fn, comp);
		comp->tq = taskqueue_create_fast("iser_taskq", M_NOWAIT,
				taskqueue_thread_enqueue, &comp->tq);
		if (!comp->tq)
			goto tq_err;
		taskqueue_start_threads(&comp->tq, 1, PI_NET, "iser taskq");
	}

	device->mr = device->pd->__internal_mr;
	if (IS_ERR(device->mr))
		goto tq_err;

	INIT_IB_EVENT_HANDLER(&device->event_handler, device->ib_device,
				iser_event_handler);
	if (ib_register_event_handler(&device->event_handler))
		goto tq_err;

	return (0);

tq_err:
	for (i = 0; i < device->comps_used; i++) {
		struct iser_comp *comp = &device->comps[i];
		if (comp->tq)
			taskqueue_free(comp->tq);
	}
cq_err:
	for (i = 0; i < device->comps_used; i++) {
		struct iser_comp *comp = &device->comps[i];
		if (comp->cq)
			ib_destroy_cq(comp->cq);
	}
	ib_dealloc_pd(device->pd);
pd_err:
	free(device->comps, M_ISER_VERBS);
comps_err:
	ISER_ERR("failed to allocate an IB resource");
	return (1);
}