#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct nvme_request {int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  nvme_cb_fn_t ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_REQUEST_NULL ; 
 struct nvme_request* _nvme_allocate_request (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static __inline struct nvme_request *
nvme_allocate_request_null(nvme_cb_fn_t cb_fn, void *cb_arg)
{
	struct nvme_request *req;

	req = _nvme_allocate_request(cb_fn, cb_arg);
	if (req != NULL)
		req->type = NVME_REQUEST_NULL;
	return (req);
}