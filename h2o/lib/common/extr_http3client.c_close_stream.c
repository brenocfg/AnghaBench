#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct st_h2o_http3client_req_t {TYPE_1__* quic; } ;
struct TYPE_3__ {int /*<<< orphan*/  recvstate; int /*<<< orphan*/  sendstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  detach_stream (struct st_h2o_http3client_req_t*) ; 
 int /*<<< orphan*/  quicly_recvstate_transfer_complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  quicly_request_stop (TYPE_1__*,int) ; 
 int /*<<< orphan*/  quicly_reset_stream (TYPE_1__*,int) ; 
 int /*<<< orphan*/  quicly_sendstate_transfer_complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void close_stream(struct st_h2o_http3client_req_t *req, int err)
{
    /* TODO are we expected to send two error codes? */
    if (!quicly_sendstate_transfer_complete(&req->quic->sendstate))
        quicly_reset_stream(req->quic, err);
    if (!quicly_recvstate_transfer_complete(&req->quic->recvstate))
        quicly_request_stop(req->quic, err);
    detach_stream(req);
}