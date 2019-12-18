#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;

/* Type definitions */
struct TYPE_28__ {TYPE_4__* priv; } ;
typedef  TYPE_3__ svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_ra_serf__xml_context_t ;
struct TYPE_26__ {int /*<<< orphan*/  path; } ;
struct TYPE_29__ {TYPE_1__ session_url; } ;
typedef  TYPE_4__ svn_ra_serf__session_t ;
struct TYPE_27__ {int code; } ;
struct TYPE_30__ {char* method; char const* path; char* body_type; TYPE_2__ sline; TYPE_7__* body_delegate_baton; int /*<<< orphan*/  body_delegate; } ;
typedef  TYPE_5__ svn_ra_serf__handler_t ;
struct TYPE_31__ {scalar_t__ apr_err; } ;
typedef  TYPE_6__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
struct TYPE_32__ {int /*<<< orphan*/ * hash; int /*<<< orphan*/  requested_depth; int /*<<< orphan*/  path; int /*<<< orphan*/ * pool; } ;
typedef  TYPE_7__ lock_context_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_ERR_FS_NOT_FOUND ; 
 int /*<<< orphan*/  SVN_ERR_RA_NOT_IMPLEMENTED ; 
 int /*<<< orphan*/  SVN_ERR_UNSUPPORTED_FEATURE ; 
 TYPE_6__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_VA_NULL ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 TYPE_7__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  apr_pstrcat (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_getlocks_body ; 
 int /*<<< orphan*/  getlocks_closed ; 
 int /*<<< orphan*/  getlocks_ttable ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_6__*) ; 
 TYPE_6__* svn_error_create (int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_error_find_cause (TYPE_6__*,int /*<<< orphan*/ ) ; 
 TYPE_6__* svn_error_trace (TYPE_6__*) ; 
 char* svn_path_url_add_component2 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 TYPE_6__* svn_ra_serf__context_run_one (TYPE_5__*,int /*<<< orphan*/ *) ; 
 TYPE_5__* svn_ra_serf__create_expat_handler (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_serf__get_relative_path (char const**,char const*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 TYPE_6__* svn_ra_serf__unexpected_status (TYPE_5__*) ; 
 int /*<<< orphan*/ * svn_ra_serf__xml_context_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_7__*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_ra_serf__get_locks(svn_ra_session_t *ra_session,
                       apr_hash_t **locks,
                       const char *path,
                       svn_depth_t depth,
                       apr_pool_t *pool)
{
  lock_context_t *lock_ctx;
  svn_ra_serf__session_t *session = ra_session->priv;
  svn_ra_serf__handler_t *handler;
  svn_ra_serf__xml_context_t *xmlctx;
  const char *req_url, *rel_path;
  svn_error_t *err;

  req_url = svn_path_url_add_component2(session->session_url.path, path, pool);
  SVN_ERR(svn_ra_serf__get_relative_path(&rel_path, req_url, session, pool));

  lock_ctx = apr_pcalloc(pool, sizeof(*lock_ctx));
  lock_ctx->pool = pool;
  lock_ctx->path = apr_pstrcat(pool, "/", rel_path, SVN_VA_NULL);
  lock_ctx->requested_depth = depth;
  lock_ctx->hash = apr_hash_make(pool);

  xmlctx = svn_ra_serf__xml_context_create(getlocks_ttable,
                                           NULL, getlocks_closed, NULL,
                                           lock_ctx,
                                           pool);
  handler = svn_ra_serf__create_expat_handler(session, xmlctx, NULL, pool);

  handler->method = "REPORT";
  handler->path = req_url;
  handler->body_type = "text/xml";

  handler->body_delegate = create_getlocks_body;
  handler->body_delegate_baton = lock_ctx;

  err = svn_ra_serf__context_run_one(handler, pool);

  if (err)
    {
      if (svn_error_find_cause(err, SVN_ERR_UNSUPPORTED_FEATURE))
        {
          /* The server told us that it doesn't support this report type.
             We return the documented error for svn_ra_get_locks(), but
             with the original error report */
          return svn_error_create(SVN_ERR_RA_NOT_IMPLEMENTED, err, NULL);
        }
      else if (err->apr_err == SVN_ERR_FS_NOT_FOUND)
        {
          /* File doesn't exist in HEAD: Not an error */
          svn_error_clear(err);
        }
      else
        return svn_error_trace(err);
    }

  /* We get a 404 when a path doesn't exist in HEAD, but it might
     have existed earlier (E.g. 'svn ls http://s/svn/trunk/file@1' */
  if (handler->sline.code != 200
      && handler->sline.code != 404)
    {
      return svn_error_trace(svn_ra_serf__unexpected_status(handler));
    }

  *locks = lock_ctx->hash;

  return SVN_NO_ERROR;
}