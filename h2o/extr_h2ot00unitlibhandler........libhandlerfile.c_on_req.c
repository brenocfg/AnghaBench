#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
struct st_h2o_sendfile_generator_t {int dummy; } ;
struct TYPE_27__ {scalar_t__ base; scalar_t__ len; } ;
struct TYPE_30__ {size_t len; int /*<<< orphan*/ * base; } ;
struct TYPE_28__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
struct TYPE_29__ {scalar_t__ query_at; TYPE_3__ path; int /*<<< orphan*/  pool; TYPE_6__ path_normalized; TYPE_4__ method; } ;
typedef  TYPE_5__ h2o_req_t ;
typedef  TYPE_6__ h2o_iovec_t ;
typedef  int /*<<< orphan*/  h2o_handler_t ;
struct TYPE_26__ {size_t len; int /*<<< orphan*/ * base; } ;
struct TYPE_25__ {size_t len; int /*<<< orphan*/ * base; } ;
struct TYPE_31__ {size_t max_index_file_len; int flags; int /*<<< orphan*/  mimemap; TYPE_6__* index_files; TYPE_2__ real_path; TYPE_1__ conf_path; } ;
typedef  TYPE_7__ h2o_file_handler_t ;

/* Variables and functions */
 scalar_t__ EMFILE ; 
 scalar_t__ ENFILE ; 
 scalar_t__ ENOENT ; 
 scalar_t__ ENOTDIR ; 
 int H2O_FILE_FLAG_DIR_LISTING ; 
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 scalar_t__ SIZE_MAX ; 
 char* alloca (size_t) ; 
 struct st_h2o_sendfile_generator_t* create_generator (TYPE_5__*,char*,size_t,int*,int) ; 
 scalar_t__ errno ; 
 TYPE_6__ h2o_concat (int /*<<< orphan*/ *,TYPE_6__,TYPE_6__,...) ; 
 int /*<<< orphan*/  h2o_get_filext (char*,size_t) ; 
 TYPE_6__ h2o_iovec_init (scalar_t__,...) ; 
 scalar_t__ h2o_memis (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_mimemap_get_type_by_extension (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ h2o_mimemap_has_dynamic_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_resp_add_date_header (TYPE_5__*) ; 
 int /*<<< orphan*/  h2o_send_error_403 (TYPE_5__*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_send_error_503 (TYPE_5__*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_send_redirect (TYPE_5__*,int,char*,int /*<<< orphan*/ *,size_t) ; 
 TYPE_6__ h2o_uri_escape (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,char*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ send_dir_listing (TYPE_5__*,char*,size_t,int) ; 
 int /*<<< orphan*/  send_method_not_allowed (TYPE_5__*) ; 
 int serve_with_generator (struct st_h2o_sendfile_generator_t*,TYPE_5__*,TYPE_6__,char*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ try_dynamic_request (TYPE_7__*,TYPE_5__*,char*,size_t) ; 

__attribute__((used)) static int on_req(h2o_handler_t *_self, h2o_req_t *req)
{
    h2o_file_handler_t *self = (void *)_self;
    char *rpath;
    size_t rpath_len, req_path_prefix;
    struct st_h2o_sendfile_generator_t *generator = NULL;
    int is_dir;

    if (req->path_normalized.len < self->conf_path.len) {
        h2o_iovec_t dest = h2o_uri_escape(&req->pool, self->conf_path.base, self->conf_path.len, "/");
        if (req->query_at != SIZE_MAX)
            dest = h2o_concat(&req->pool, dest, h2o_iovec_init(req->path.base + req->query_at, req->path.len - req->query_at));
        h2o_send_redirect(req, 301, "Moved Permanently", dest.base, dest.len);
        return 0;
    }

    /* build path (still unterminated at the end of the block) */
    req_path_prefix = self->conf_path.len;
    rpath = alloca(self->real_path.len + (req->path_normalized.len - req_path_prefix) + self->max_index_file_len + 1);
    rpath_len = 0;
    memcpy(rpath + rpath_len, self->real_path.base, self->real_path.len);
    rpath_len += self->real_path.len;
    memcpy(rpath + rpath_len, req->path_normalized.base + req_path_prefix, req->path_normalized.len - req_path_prefix);
    rpath_len += req->path_normalized.len - req_path_prefix;

    h2o_resp_add_date_header(req);

    h2o_iovec_t resolved_path = req->path_normalized;

    /* build generator (as well as terminating the rpath and its length upon success) */
    if (rpath[rpath_len - 1] == '/') {
        h2o_iovec_t *index_file;
        for (index_file = self->index_files; index_file->base != NULL; ++index_file) {
            memcpy(rpath + rpath_len, index_file->base, index_file->len);
            rpath[rpath_len + index_file->len] = '\0';
            if ((generator = create_generator(req, rpath, rpath_len + index_file->len, &is_dir, self->flags)) != NULL) {
                rpath_len += index_file->len;
                resolved_path = h2o_concat(&req->pool, req->path_normalized, *index_file);
                goto Opened;
            }
            if (is_dir) {
                /* note: apache redirects "path/" to "path/index.txt/" if index.txt is a dir */
                h2o_iovec_t dest = h2o_concat(&req->pool, req->path_normalized, *index_file, h2o_iovec_init(H2O_STRLIT("/")));
                dest = h2o_uri_escape(&req->pool, dest.base, dest.len, "/");
                if (req->query_at != SIZE_MAX)
                    dest =
                        h2o_concat(&req->pool, dest, h2o_iovec_init(req->path.base + req->query_at, req->path.len - req->query_at));
                h2o_send_redirect(req, 301, "Moved Permantently", dest.base, dest.len);
                return 0;
            }
            if (errno != ENOENT)
                break;
        }
        if (index_file->base == NULL && (self->flags & H2O_FILE_FLAG_DIR_LISTING) != 0) {
            rpath[rpath_len] = '\0';
            int is_get = 0;
            if (h2o_memis(req->method.base, req->method.len, H2O_STRLIT("GET"))) {
                is_get = 1;
            } else if (h2o_memis(req->method.base, req->method.len, H2O_STRLIT("HEAD"))) {
                /* ok */
            } else {
                send_method_not_allowed(req);
                return 0;
            }
            if (send_dir_listing(req, rpath, rpath_len, is_get) == 0)
                return 0;
        }
    } else {
        rpath[rpath_len] = '\0';
        if ((generator = create_generator(req, rpath, rpath_len, &is_dir, self->flags)) != NULL)
            goto Opened;
        if (is_dir) {
            h2o_iovec_t dest = h2o_concat(&req->pool, req->path_normalized, h2o_iovec_init(H2O_STRLIT("/")));
            dest = h2o_uri_escape(&req->pool, dest.base, dest.len, "/");
            if (req->query_at != SIZE_MAX)
                dest = h2o_concat(&req->pool, dest, h2o_iovec_init(req->path.base + req->query_at, req->path.len - req->query_at));
            h2o_send_redirect(req, 301, "Moved Permanently", dest.base, dest.len);
            return 0;
        }
    }
    /* failed to open */

    if (errno == ENFILE || errno == EMFILE) {
        h2o_send_error_503(req, "Service Unavailable", "please try again later", 0);
    } else {
        if (h2o_mimemap_has_dynamic_type(self->mimemap) && try_dynamic_request(self, req, rpath, rpath_len) == 0)
            return 0;
        if (errno == ENOENT || errno == ENOTDIR) {
            return -1;
        } else {
            h2o_send_error_403(req, "Access Forbidden", "access forbidden", 0);
        }
    }
    return 0;

Opened:
    return serve_with_generator(generator, req, resolved_path, rpath, rpath_len,
                                h2o_mimemap_get_type_by_extension(self->mimemap, h2o_get_filext(rpath, rpath_len)));
}