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
struct TYPE_3__ {int /*<<< orphan*/  _timeout; } ;
struct TYPE_4__ {int /*<<< orphan*/  noncontiguous; int /*<<< orphan*/  partial_frame; int /*<<< orphan*/  body; } ;
struct st_h2o_http3client_req_t {int /*<<< orphan*/  link; TYPE_1__ super; TYPE_2__ recvbuf; int /*<<< orphan*/  sendbuf; int /*<<< orphan*/ * quic; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct st_h2o_http3client_req_t*) ; 
 int /*<<< orphan*/  h2o_buffer_dispose (int /*<<< orphan*/ *) ; 
 scalar_t__ h2o_linklist_is_linked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_linklist_unlink (int /*<<< orphan*/ *) ; 
 scalar_t__ h2o_timer_is_linked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_timer_unlink (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void destroy_request(struct st_h2o_http3client_req_t *req)
{
    assert(req->quic == NULL);
    h2o_buffer_dispose(&req->sendbuf);
    h2o_buffer_dispose(&req->recvbuf.body);
    h2o_buffer_dispose(&req->recvbuf.partial_frame);
    h2o_buffer_dispose(&req->recvbuf.noncontiguous);
    if (h2o_timer_is_linked(&req->super._timeout))
        h2o_timer_unlink(&req->super._timeout);
    if (h2o_linklist_is_linked(&req->link))
        h2o_linklist_unlink(&req->link);
    free(req);
}