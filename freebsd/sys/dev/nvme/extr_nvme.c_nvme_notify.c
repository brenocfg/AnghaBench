#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ nsze; } ;
struct nvme_namespace {int /*<<< orphan*/ * cons_cookie; TYPE_2__ data; } ;
struct TYPE_3__ {int /*<<< orphan*/  nn; } ;
struct nvme_controller {struct nvme_namespace* ns; TYPE_1__ cdata; int /*<<< orphan*/ ** cons_cookie; scalar_t__ is_failed; int /*<<< orphan*/  notification_sent; int /*<<< orphan*/  is_initialized; } ;
struct nvme_consumer {size_t id; int /*<<< orphan*/  (* ns_fn ) (struct nvme_namespace*,void*) ;int /*<<< orphan*/  (* fail_fn ) (void*) ;void* (* ctrlr_fn ) (struct nvme_controller*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_MAX_NAMESPACES ; 
 int atomic_cmpset_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* stub1 (struct nvme_controller*) ; 
 int /*<<< orphan*/  stub2 (void*) ; 
 int /*<<< orphan*/  stub3 (struct nvme_namespace*,void*) ; 

__attribute__((used)) static void
nvme_notify(struct nvme_consumer *cons,
	    struct nvme_controller *ctrlr)
{
	struct nvme_namespace	*ns;
	void			*ctrlr_cookie;
	int			cmpset, ns_idx;

	/*
	 * The consumer may register itself after the nvme devices
	 *  have registered with the kernel, but before the
	 *  driver has completed initialization.  In that case,
	 *  return here, and when initialization completes, the
	 *  controller will make sure the consumer gets notified.
	 */
	if (!ctrlr->is_initialized)
		return;

	cmpset = atomic_cmpset_32(&ctrlr->notification_sent, 0, 1);
	if (cmpset == 0)
		return;

	if (cons->ctrlr_fn != NULL)
		ctrlr_cookie = (*cons->ctrlr_fn)(ctrlr);
	else
		ctrlr_cookie = (void *)(uintptr_t)0xdeadc0dedeadc0de;
	ctrlr->cons_cookie[cons->id] = ctrlr_cookie;

	/* ctrlr_fn has failed.  Nothing to notify here any more. */
	if (ctrlr_cookie == NULL)
		return;

	if (ctrlr->is_failed) {
		ctrlr->cons_cookie[cons->id] = NULL;
		if (cons->fail_fn != NULL)
			(*cons->fail_fn)(ctrlr_cookie);
		/*
		 * Do not notify consumers about the namespaces of a
		 *  failed controller.
		 */
		return;
	}
	for (ns_idx = 0; ns_idx < min(ctrlr->cdata.nn, NVME_MAX_NAMESPACES); ns_idx++) {
		ns = &ctrlr->ns[ns_idx];
		if (ns->data.nsze == 0)
			continue;
		if (cons->ns_fn != NULL)
			ns->cons_cookie[cons->id] =
			    (*cons->ns_fn)(ns, ctrlr_cookie);
	}
}