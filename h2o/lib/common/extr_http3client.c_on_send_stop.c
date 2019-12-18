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
struct st_h2o_http3client_req_t {int dummy; } ;
struct TYPE_3__ {struct st_h2o_http3client_req_t* data; } ;
typedef  TYPE_1__ quicly_stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_HTTP3_ERROR_REQUEST_CANCELLED ; 
 int /*<<< orphan*/  close_stream (struct st_h2o_http3client_req_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_request (struct st_h2o_http3client_req_t*) ; 
 int /*<<< orphan*/  handle_input_error (struct st_h2o_http3client_req_t*,int) ; 

__attribute__((used)) static int on_send_stop(quicly_stream_t *qs, int err)
{
    struct st_h2o_http3client_req_t *req;

    if ((req = qs->data) == NULL)
        return 0;
    handle_input_error(req, err);
    close_stream(req, H2O_HTTP3_ERROR_REQUEST_CANCELLED);
    destroy_request(req);

    return 0;
}