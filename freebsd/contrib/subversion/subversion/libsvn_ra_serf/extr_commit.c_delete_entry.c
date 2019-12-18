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
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_13__ {int code; } ;
struct TYPE_14__ {char* method; char const* path; char* body_type; TYPE_1__ sline; scalar_t__ server_error; TYPE_4__* body_delegate_baton; int /*<<< orphan*/  body_delegate; TYPE_4__* header_delegate_baton; void* header_delegate; struct TYPE_14__* response_baton; void* response_handler; void* no_fail_on_http_failure_status; } ;
typedef  TYPE_2__ svn_ra_serf__handler_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_15__ {TYPE_11__* commit_ctx; int /*<<< orphan*/  working_url; int /*<<< orphan*/ * pool; } ;
typedef  TYPE_3__ dir_context_t ;
struct TYPE_16__ {void* non_recursive_if; TYPE_11__* commit_ctx; int /*<<< orphan*/  revision; int /*<<< orphan*/  relpath; } ;
typedef  TYPE_4__ delete_context_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_12__ {int /*<<< orphan*/ * pool; int /*<<< orphan*/  deleted_entries; int /*<<< orphan*/  session; int /*<<< orphan*/  txn_root_url; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 void* TRUE ; 
 scalar_t__ USING_HTTPV2_COMMIT_SUPPORT (TYPE_11__*) ; 
 TYPE_4__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  checkout_dir (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  create_delete_body ; 
 void* setup_delete_headers ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 char* svn_path_url_add_component2 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_serf__context_run_one (TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_ra_serf__create_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* svn_ra_serf__expect_empty_body ; 
 int /*<<< orphan*/ * svn_ra_serf__server_error_create (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_serf__unexpected_status (TYPE_2__*) ; 
 char const* svn_relpath_basename (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
delete_entry(const char *path,
             svn_revnum_t revision,
             void *parent_baton,
             apr_pool_t *pool)
{
  dir_context_t *dir = parent_baton;
  delete_context_t *delete_ctx;
  svn_ra_serf__handler_t *handler;
  const char *delete_target;

  if (USING_HTTPV2_COMMIT_SUPPORT(dir->commit_ctx))
    {
      delete_target = svn_path_url_add_component2(
                                    dir->commit_ctx->txn_root_url,
                                    path, dir->pool);
    }
  else
    {
      /* Ensure our directory has been checked out */
      SVN_ERR(checkout_dir(dir, pool /* scratch_pool */));
      delete_target = svn_path_url_add_component2(dir->working_url,
                                                  svn_relpath_basename(path,
                                                                       NULL),
                                                  pool);
    }

  /* DELETE our entry */
  delete_ctx = apr_pcalloc(pool, sizeof(*delete_ctx));
  delete_ctx->relpath = apr_pstrdup(pool, path);
  delete_ctx->revision = revision;
  delete_ctx->commit_ctx = dir->commit_ctx;

  handler = svn_ra_serf__create_handler(dir->commit_ctx->session, pool);

  handler->response_handler = svn_ra_serf__expect_empty_body;
  handler->response_baton = handler;

  handler->header_delegate = setup_delete_headers;
  handler->header_delegate_baton = delete_ctx;

  handler->method = "DELETE";
  handler->path = delete_target;
  handler->no_fail_on_http_failure_status = TRUE;

  SVN_ERR(svn_ra_serf__context_run_one(handler, pool));

  if (handler->sline.code == 400)
    {
      /* Try again with non-standard body to overcome Apache Httpd
         header limit */
      delete_ctx->non_recursive_if = TRUE;

      handler = svn_ra_serf__create_handler(dir->commit_ctx->session, pool);

      handler->response_handler = svn_ra_serf__expect_empty_body;
      handler->response_baton = handler;

      handler->header_delegate = setup_delete_headers;
      handler->header_delegate_baton = delete_ctx;

      handler->method = "DELETE";
      handler->path = delete_target;

      handler->body_type = "text/xml";
      handler->body_delegate = create_delete_body;
      handler->body_delegate_baton = delete_ctx;

      SVN_ERR(svn_ra_serf__context_run_one(handler, pool));
    }

  if (handler->server_error)
    return svn_ra_serf__server_error_create(handler, pool);

  /* 204 No Content: item successfully deleted */
  if (handler->sline.code != 204)
    return svn_error_trace(svn_ra_serf__unexpected_status(handler));

  svn_hash_sets(dir->commit_ctx->deleted_entries,
                apr_pstrdup(dir->commit_ctx->pool, path), (void *)1);

  return SVN_NO_ERROR;
}