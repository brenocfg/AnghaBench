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
struct TYPE_2__ {int /*<<< orphan*/ * respool; int /*<<< orphan*/ * req_bkt; int /*<<< orphan*/ * resp_bkt; } ;
typedef  TYPE_1__ serf_request_t ;
typedef  int /*<<< orphan*/  apr_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SUCCESS ; 
 int /*<<< orphan*/  serf_bucket_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static apr_status_t clean_resp(void *data)
{
    serf_request_t *request = data;

    /* The request's RESPOOL is being cleared.  */

    /* If the response has allocated some buckets, then destroy them (since
       the bucket may hold resources other than memory in RESPOOL). Also
       make sure to set their fields to NULL so connection closure does
       not attempt to free them again.  */
    if (request->resp_bkt) {
        serf_bucket_destroy(request->resp_bkt);
        request->resp_bkt = NULL;
    }
    if (request->req_bkt) {
        serf_bucket_destroy(request->req_bkt);
        request->req_bkt = NULL;
    }

    /* ### should we worry about debug stuff, like that performed in
       ### destroy_request()? should we worry about calling req->handler
       ### to notify this "cancellation" due to pool clearing?  */

    /* This pool just got cleared/destroyed. Don't try to destroy the pool
       (again) when the request is canceled.  */
    request->respool = NULL;

    return APR_SUCCESS;
}