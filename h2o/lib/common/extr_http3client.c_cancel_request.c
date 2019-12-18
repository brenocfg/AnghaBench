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
struct st_h2o_http3client_req_t {int /*<<< orphan*/ * quic; } ;
typedef  int /*<<< orphan*/  h2o_httpclient_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_HTTP3_ERROR_REQUEST_CANCELLED ; 
 int /*<<< orphan*/  close_stream (struct st_h2o_http3client_req_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_request (struct st_h2o_http3client_req_t*) ; 

__attribute__((used)) static void cancel_request(h2o_httpclient_t *_client)
{
    struct st_h2o_http3client_req_t *req = (void *)_client;
    if (req->quic != NULL)
        close_stream(req, H2O_HTTP3_ERROR_REQUEST_CANCELLED);
    destroy_request(req);
}