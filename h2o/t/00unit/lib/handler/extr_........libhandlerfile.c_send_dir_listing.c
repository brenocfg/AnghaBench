#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int status; char* reason; int /*<<< orphan*/  headers; } ;
struct TYPE_14__ {TYPE_1__ res; int /*<<< orphan*/  pool; int /*<<< orphan*/  path_normalized; } ;
typedef  TYPE_2__ h2o_req_t ;
typedef  int /*<<< orphan*/  h2o_iovec_t ;
struct TYPE_15__ {int /*<<< orphan*/ * member_1; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_3__ h2o_generator_t ;
struct TYPE_16__ {int /*<<< orphan*/  size; int /*<<< orphan*/  bytes; } ;
typedef  TYPE_4__ h2o_buffer_t ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_SEND_STATE_FINAL ; 
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 int /*<<< orphan*/  H2O_TOKEN_CONTENT_TYPE ; 
 TYPE_4__* build_dir_listing_html (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_add_header (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_buffer_link_to_pool (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_iovec_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_send (TYPE_2__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_send_error_503 (TYPE_2__*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_send_inline (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_start_response (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/ * opendir (char const*) ; 

__attribute__((used)) static int send_dir_listing(h2o_req_t *req, const char *path, size_t path_len, int is_get)
{
    static h2o_generator_t generator = {NULL, NULL};
    DIR *dp;
    h2o_buffer_t *body;
    h2o_iovec_t bodyvec;

    /* build html */
    if ((dp = opendir(path)) == NULL)
        return -1;
    body = build_dir_listing_html(&req->pool, req->path_normalized, dp);
    closedir(dp);

    if (body == NULL) {
        h2o_send_error_503(req, "Service Unavailable", "please try again later", 0);
        return 0;
    }

    bodyvec = h2o_iovec_init(body->bytes, body->size);
    h2o_buffer_link_to_pool(body, &req->pool);

    /* send response */
    req->res.status = 200;
    req->res.reason = "OK";
    h2o_add_header(&req->pool, &req->res.headers, H2O_TOKEN_CONTENT_TYPE, NULL, H2O_STRLIT("text/html; charset=utf-8"));

    /* send headers */
    if (!is_get) {
        h2o_send_inline(req, NULL, 0);
        return 0;
    }

    /* send data */
    h2o_start_response(req, &generator);
    h2o_send(req, &bodyvec, 1, H2O_SEND_STATE_FINAL);
    return 0;
}