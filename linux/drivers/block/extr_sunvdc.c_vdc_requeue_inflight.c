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
typedef  size_t u32 ;
struct vio_dring_state {size_t cons; size_t prod; } ;
struct TYPE_4__ {int /*<<< orphan*/  state; } ;
struct vio_disk_desc {TYPE_2__ hdr; int /*<<< orphan*/  ncookies; int /*<<< orphan*/  cookies; } ;
struct vdc_req_entry {struct request* req; } ;
struct TYPE_3__ {int /*<<< orphan*/  lp; struct vio_dring_state* drings; } ;
struct vdc_port {TYPE_1__ vio; struct vdc_req_entry* rq_arr; } ;
struct request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIO_DESC_FREE ; 
 size_t VIO_DRIVER_TX_RING ; 
 int /*<<< orphan*/  blk_mq_requeue_request (struct request*,int) ; 
 int /*<<< orphan*/  ldc_unmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdc_end_special (struct vdc_port*,struct vio_disk_desc*) ; 
 struct vio_disk_desc* vio_dring_entry (struct vio_dring_state*,size_t) ; 
 void* vio_dring_next (struct vio_dring_state*,size_t) ; 

__attribute__((used)) static void vdc_requeue_inflight(struct vdc_port *port)
{
	struct vio_dring_state *dr = &port->vio.drings[VIO_DRIVER_TX_RING];
	u32 idx;

	for (idx = dr->cons; idx != dr->prod; idx = vio_dring_next(dr, idx)) {
		struct vio_disk_desc *desc = vio_dring_entry(dr, idx);
		struct vdc_req_entry *rqe = &port->rq_arr[idx];
		struct request *req;

		ldc_unmap(port->vio.lp, desc->cookies, desc->ncookies);
		desc->hdr.state = VIO_DESC_FREE;
		dr->cons = vio_dring_next(dr, idx);

		req = rqe->req;
		if (req == NULL) {
			vdc_end_special(port, desc);
			continue;
		}

		rqe->req = NULL;
		blk_mq_requeue_request(req, false);
	}
}