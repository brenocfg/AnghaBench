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
struct TYPE_8__ {int /*<<< orphan*/  etag; } ;
struct TYPE_7__ {int /*<<< orphan*/  ref; } ;
struct st_h2o_sendfile_generator_t {scalar_t__ send_vary; TYPE_3__ header_bufs; TYPE_2__ file; scalar_t__ send_etag; } ;
struct TYPE_6__ {int /*<<< orphan*/  headers; } ;
struct TYPE_9__ {TYPE_1__ res; int /*<<< orphan*/  pool; } ;
typedef  TYPE_4__ h2o_req_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 int /*<<< orphan*/  H2O_TOKEN_ETAG ; 
 int /*<<< orphan*/  H2O_TOKEN_VARY ; 
 int /*<<< orphan*/  h2o_add_header (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 size_t h2o_filecache_get_etag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_set_header_token (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void add_headers_unconditional(struct st_h2o_sendfile_generator_t *self, h2o_req_t *req)
{
    /* RFC 7232 4.1: The server generating a 304 response MUST generate any of the following header fields that would have been sent
     * in a 200 (OK) response to the same request: Cache-Control, Content-Location, Date, ETag, Expires, and Vary (snip) a sender
     * SHOULD NOT generate representation metadata other than the above listed fields unless said metadata exists for the purpose of
     * guiding cache updates. */
    if (self->send_etag) {
        size_t etag_len = h2o_filecache_get_etag(self->file.ref, self->header_bufs.etag);
        h2o_add_header(&req->pool, &req->res.headers, H2O_TOKEN_ETAG, NULL, self->header_bufs.etag, etag_len);
    }
    if (self->send_vary)
        h2o_set_header_token(&req->pool, &req->res.headers, H2O_TOKEN_VARY, H2O_STRLIT("accept-encoding"));
}