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
struct st_h2o_mruby_http_request_context_t {int /*<<< orphan*/ * client; } ;
typedef  int /*<<< orphan*/  headers ;
typedef  int /*<<< orphan*/  h2o_iovec_t ;
struct TYPE_3__ {struct st_h2o_mruby_http_request_context_t* data; } ;
typedef  TYPE_1__ h2o_httpclient_t ;
typedef  int /*<<< orphan*/ * h2o_httpclient_body_cb ;
typedef  int /*<<< orphan*/  h2o_header_t ;

/* Variables and functions */
 char const* h2o_httpclient_error_is_eos ; 
 int /*<<< orphan*/  headers_sort_cb ; 
 int /*<<< orphan*/ * on_body ; 
 int /*<<< orphan*/  post_error (struct st_h2o_mruby_http_request_context_t*,char const*) ; 
 int /*<<< orphan*/  post_response (struct st_h2o_mruby_http_request_context_t*,int,int /*<<< orphan*/ *,size_t,int) ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static h2o_httpclient_body_cb do_on_head(h2o_httpclient_t *client, const char *errstr, int version, int status, h2o_iovec_t msg,
                                         h2o_header_t *headers, size_t num_headers, int header_requires_dup)
{
    struct st_h2o_mruby_http_request_context_t *ctx = client->data;

    if (errstr != NULL) {
        if (errstr != h2o_httpclient_error_is_eos) {
            /* error */
            post_error(ctx, errstr);
            return NULL;
        }
        /* closed without body */
        ctx->client = NULL;
    }

    qsort(headers, num_headers, sizeof(headers[0]), headers_sort_cb);
    post_response(ctx, status, headers, num_headers, header_requires_dup);

    return on_body;
}