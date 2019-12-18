#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_37__   TYPE_7__ ;
typedef  struct TYPE_36__   TYPE_6__ ;
typedef  struct TYPE_35__   TYPE_5__ ;
typedef  struct TYPE_34__   TYPE_4__ ;
typedef  struct TYPE_33__   TYPE_3__ ;
typedef  struct TYPE_32__   TYPE_2__ ;
typedef  struct TYPE_31__   TYPE_26__ ;
typedef  struct TYPE_30__   TYPE_1__ ;
typedef  struct TYPE_29__   TYPE_12__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_30__ {int code; } ;
struct TYPE_33__ {char* method; char const* path; void* no_dav_headers; struct TYPE_33__* response_baton; void* response_handler; TYPE_1__ sline; TYPE_5__* header_delegate_baton; int /*<<< orphan*/  header_delegate; } ;
typedef  TYPE_3__ svn_ra_serf__handler_t ;
struct TYPE_34__ {scalar_t__ apr_err; } ;
typedef  TYPE_4__ svn_error_t ;
struct TYPE_35__ {char const* name; int /*<<< orphan*/ * pool; void* url; int /*<<< orphan*/  prop_changes; int /*<<< orphan*/  copy_revision; void* copy_path; int /*<<< orphan*/  base_revision; void* added; void* relpath; TYPE_26__* commit_ctx; TYPE_6__* parent_dir; } ;
typedef  TYPE_5__ file_context_t ;
struct TYPE_36__ {TYPE_26__* commit_ctx; int /*<<< orphan*/  copy_path; scalar_t__ added; int /*<<< orphan*/  working_url; } ;
typedef  TYPE_6__ dir_context_t ;
struct TYPE_37__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_7__ apr_uri_t ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_32__ {int /*<<< orphan*/  path; } ;
struct TYPE_31__ {TYPE_12__* session; int /*<<< orphan*/  deleted_entries; int /*<<< orphan*/  txn_root_url; int /*<<< orphan*/  open_batons; } ;
struct TYPE_29__ {TYPE_2__ session_url; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (TYPE_4__*) ; 
 int /*<<< orphan*/  SVN_ERR_FS_ALREADY_EXISTS ; 
 scalar_t__ SVN_ERR_FS_NOT_FOUND ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 TYPE_4__* SVN_NO_ERROR ; 
 void* TRUE ; 
 scalar_t__ USING_HTTPV2_COMMIT_SUPPORT (TYPE_26__*) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  apr_hash_make (int /*<<< orphan*/ *) ; 
 TYPE_5__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 void* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ apr_uri_parse (int /*<<< orphan*/ *,char const*,TYPE_7__*) ; 
 TYPE_4__* checkout_dir (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_copy_file_headers ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_4__*) ; 
 TYPE_4__* svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 TYPE_4__* svn_error_trace (TYPE_4__*) ; 
 scalar_t__ svn_hash_gets (int /*<<< orphan*/ ,char const*) ; 
 void* svn_path_url_add_component2 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 TYPE_4__* svn_ra_serf__context_run_one (TYPE_3__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_ra_serf__create_handler (TYPE_12__*,int /*<<< orphan*/ *) ; 
 void* svn_ra_serf__expect_empty_body ; 
 TYPE_4__* svn_ra_serf__get_stable_url (char const**,int /*<<< orphan*/ *,TYPE_12__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* svn_ra_serf__unexpected_status (TYPE_3__*) ; 
 TYPE_4__* svn_ra_serf__wrap_err (scalar_t__,int /*<<< orphan*/ *) ; 
 char const* svn_relpath_basename (void*,int /*<<< orphan*/ *) ; 
 char* svn_relpath_dirname (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
add_file(const char *path,
         void *parent_baton,
         const char *copy_path,
         svn_revnum_t copy_revision,
         apr_pool_t *file_pool,
         void **file_baton)
{
  dir_context_t *dir = parent_baton;
  file_context_t *new_file;
  const char *deleted_parent = path;
  apr_pool_t *scratch_pool = svn_pool_create(file_pool);

  new_file = apr_pcalloc(file_pool, sizeof(*new_file));
  new_file->pool = file_pool;

  new_file->parent_dir = dir;
  new_file->commit_ctx = dir->commit_ctx;
  new_file->relpath = apr_pstrdup(new_file->pool, path);
  new_file->name = svn_relpath_basename(new_file->relpath, NULL);
  new_file->added = TRUE;
  new_file->base_revision = SVN_INVALID_REVNUM;
  new_file->copy_path = apr_pstrdup(new_file->pool, copy_path);
  new_file->copy_revision = copy_revision;
  new_file->prop_changes = apr_hash_make(new_file->pool);

  dir->commit_ctx->open_batons++;

  /* Ensure that the file doesn't exist by doing a HEAD on the
     resource.  If we're using HTTP v2, we'll just look into the
     transaction root tree for this thing.  */
  if (USING_HTTPV2_COMMIT_SUPPORT(dir->commit_ctx))
    {
      new_file->url = svn_path_url_add_component2(dir->commit_ctx->txn_root_url,
                                                  path, new_file->pool);
    }
  else
    {
      /* Ensure our parent directory has been checked out */
      SVN_ERR(checkout_dir(dir, scratch_pool));

      new_file->url =
        svn_path_url_add_component2(dir->working_url,
                                    new_file->name, new_file->pool);
    }

  while (deleted_parent && deleted_parent[0] != '\0')
    {
      if (svn_hash_gets(dir->commit_ctx->deleted_entries, deleted_parent))
        {
          break;
        }
      deleted_parent = svn_relpath_dirname(deleted_parent, file_pool);
    }

  if (copy_path)
    {
      svn_ra_serf__handler_t *handler;
      apr_uri_t uri;
      const char *req_url;
      apr_status_t status;

      /* Create the copy directly as cheap 'does exist/out of date'
         check. We update the copy (if needed) from close_file() */

      status = apr_uri_parse(scratch_pool, copy_path, &uri);
      if (status)
        return svn_ra_serf__wrap_err(status, NULL);

      SVN_ERR(svn_ra_serf__get_stable_url(&req_url, NULL /* latest_revnum */,
                                          dir->commit_ctx->session,
                                          uri.path, copy_revision,
                                          scratch_pool, scratch_pool));

      handler = svn_ra_serf__create_handler(dir->commit_ctx->session,
                                            scratch_pool);
      handler->method = "COPY";
      handler->path = req_url;

      handler->response_handler = svn_ra_serf__expect_empty_body;
      handler->response_baton = handler;

      handler->header_delegate = setup_copy_file_headers;
      handler->header_delegate_baton = new_file;

      SVN_ERR(svn_ra_serf__context_run_one(handler, scratch_pool));

      if (handler->sline.code != 201)
        return svn_error_trace(svn_ra_serf__unexpected_status(handler));
    }
  else if (! ((dir->added && !dir->copy_path) ||
           (deleted_parent && deleted_parent[0] != '\0')))
    {
      svn_ra_serf__handler_t *handler;
      svn_error_t *err;

      handler = svn_ra_serf__create_handler(dir->commit_ctx->session,
                                            scratch_pool);
      handler->method = "HEAD";
      handler->path = svn_path_url_add_component2(
                                        dir->commit_ctx->session->session_url.path,
                                        path, scratch_pool);
      handler->response_handler = svn_ra_serf__expect_empty_body;
      handler->response_baton = handler;
      handler->no_dav_headers = TRUE; /* Read only operation outside txn */

      err = svn_ra_serf__context_run_one(handler, scratch_pool);

      if (err && err->apr_err == SVN_ERR_FS_NOT_FOUND)
        {
          svn_error_clear(err); /* Great. We can create a new file! */
        }
      else if (err)
        return svn_error_trace(err);
      else
        return svn_error_createf(SVN_ERR_FS_ALREADY_EXISTS, NULL,
                                 _("File '%s' already exists"), path);
    }

  svn_pool_destroy(scratch_pool);
  *file_baton = new_file;

  return SVN_NO_ERROR;
}