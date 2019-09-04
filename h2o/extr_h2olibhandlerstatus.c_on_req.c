#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct st_h2o_root_status_handler_t {int dummy; } ;
struct TYPE_21__ {int len; char const* base; } ;
struct TYPE_20__ {int /*<<< orphan*/  headers; } ;
struct TYPE_19__ {char const* base; int len; } ;
struct TYPE_22__ {int query_at; TYPE_5__ path; TYPE_4__ res; int /*<<< orphan*/  pool; TYPE_3__ path_normalized; TYPE_2__* pathconf; } ;
typedef  TYPE_6__ h2o_req_t ;
struct TYPE_23__ {scalar_t__ len; int /*<<< orphan*/  member_1; int /*<<< orphan*/ * member_0; int /*<<< orphan*/  base; } ;
typedef  TYPE_7__ h2o_iovec_t ;
typedef  int /*<<< orphan*/  h2o_handler_t ;
struct TYPE_17__ {int len; char* base; } ;
struct TYPE_18__ {TYPE_1__ path; } ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_ROOT ; 
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 int /*<<< orphan*/  H2O_TOKEN_CACHE_CONTROL ; 
 char* H2O_TO_STR (int /*<<< orphan*/ ) ; 
 int SIZE_MAX ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  h2o_add_header (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_7__ h2o_concat (int /*<<< orphan*/ *,TYPE_7__,TYPE_7__) ; 
 int h2o_file_send (TYPE_6__*,int,char*,int /*<<< orphan*/ ,TYPE_7__,int /*<<< orphan*/ ) ; 
 TYPE_7__ h2o_iovec_init (char const*,...) ; 
 scalar_t__ h2o_memis (char const*,int,char*,...) ; 
 int on_req_json (struct st_h2o_root_status_handler_t*,TYPE_6__*,TYPE_7__) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int on_req(h2o_handler_t *_self, h2o_req_t *req)
{
    struct st_h2o_root_status_handler_t *self = (void *)_self;
    size_t prefix_len = req->pathconf->path.len - (req->pathconf->path.base[req->pathconf->path.len - 1] == '/');
    h2o_iovec_t local_path = h2o_iovec_init(req->path_normalized.base + prefix_len, req->path_normalized.len - prefix_len);

    if (local_path.len == 0 || h2o_memis(local_path.base, local_path.len, H2O_STRLIT("/"))) {
        /* root of the handler returns HTML that renders the status */
        h2o_iovec_t fn;
        const char *root = getenv("H2O_ROOT");
        if (root == NULL)
            root = H2O_TO_STR(H2O_ROOT);
        fn = h2o_concat(&req->pool, h2o_iovec_init(root, strlen(root)), h2o_iovec_init(H2O_STRLIT("/share/h2o/status/index.html")));
        h2o_add_header(&req->pool, &req->res.headers, H2O_TOKEN_CACHE_CONTROL, NULL, H2O_STRLIT("no-cache"));
        return h2o_file_send(req, 200, "OK", fn.base, h2o_iovec_init(H2O_STRLIT("text/html; charset=utf-8")), 0);
    } else if (h2o_memis(local_path.base, local_path.len, H2O_STRLIT("/json"))) {
        int ret;
        /* "/json" maps to the JSON API */
        h2o_iovec_t status_list = {NULL, 0}; /* NULL means we'll show all statuses */
        if (req->query_at != SIZE_MAX && (req->path.len - req->query_at > 6)) {
            if (h2o_memis(&req->path.base[req->query_at], 6, "?show=", 6)) {
                status_list = h2o_iovec_init(&req->path.base[req->query_at + 6], req->path.len - req->query_at - 6);
            }
        }
        ret = on_req_json(self, req, status_list);
        return ret;
    }

    return -1;
}