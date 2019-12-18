#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ bytes_contiguous; TYPE_2__* partial_frame; TYPE_1__* body; } ;
struct st_h2o_http3client_req_t {TYPE_3__ recvbuf; } ;
struct TYPE_9__ {struct st_h2o_http3client_req_t* data; } ;
typedef  TYPE_4__ quicly_stream_t ;
struct TYPE_7__ {scalar_t__ size; } ;
struct TYPE_6__ {scalar_t__ size; } ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_HTTP3_ERROR_REQUEST_CANCELLED ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close_stream (struct st_h2o_http3client_req_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_request (struct st_h2o_http3client_req_t*) ; 
 int /*<<< orphan*/  handle_input_error (struct st_h2o_http3client_req_t*,int) ; 

__attribute__((used)) static int on_receive_reset(quicly_stream_t *qs, int err)
{
    struct st_h2o_http3client_req_t *req = qs->data;

    assert(req->recvbuf.body->size + req->recvbuf.partial_frame->size == req->recvbuf.bytes_contiguous);

    handle_input_error(req, err);
    close_stream(req, H2O_HTTP3_ERROR_REQUEST_CANCELLED);
    destroy_request(req);

    return 0;
}