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
struct nvme_request {int /*<<< orphan*/  timeout; void* cb_arg; int /*<<< orphan*/  cb_fn; } ;
typedef  int /*<<< orphan*/  nvme_cb_fn_t ;

/* Variables and functions */
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  nvme_request_zone ; 
 struct nvme_request* uma_zalloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static __inline struct nvme_request *
_nvme_allocate_request(nvme_cb_fn_t cb_fn, void *cb_arg)
{
	struct nvme_request *req;

	req = uma_zalloc(nvme_request_zone, M_NOWAIT | M_ZERO);
	if (req != NULL) {
		req->cb_fn = cb_fn;
		req->cb_arg = cb_arg;
		req->timeout = TRUE;
	}
	return (req);
}