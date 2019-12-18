#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {void* payload; } ;
struct nvme_request {int /*<<< orphan*/  payload_size; TYPE_1__ u; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  nvme_cb_fn_t ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_REQUEST_VADDR ; 
 struct nvme_request* _nvme_allocate_request (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static __inline struct nvme_request *
nvme_allocate_request_vaddr(void *payload, uint32_t payload_size,
    nvme_cb_fn_t cb_fn, void *cb_arg)
{
	struct nvme_request *req;

	req = _nvme_allocate_request(cb_fn, cb_arg);
	if (req != NULL) {
		req->type = NVME_REQUEST_VADDR;
		req->u.payload = payload;
		req->payload_size = payload_size;
	}
	return (req);
}