#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  void* svn_revnum_t ;
struct TYPE_11__ {int /*<<< orphan*/ * priv; } ;
typedef  TYPE_2__ svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_ra_serf__xml_context_t ;
typedef  int /*<<< orphan*/  svn_ra_serf__session_t ;
struct TYPE_10__ {int code; } ;
struct TYPE_12__ {char* method; char const* path; char* body_type; TYPE_1__ sline; TYPE_4__* body_delegate_baton; int /*<<< orphan*/  body_delegate; } ;
typedef  TYPE_3__ svn_ra_serf__handler_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_13__ {char const* path; void** revision_deleted; void* end_revision; void* peg_revision; } ;
typedef  TYPE_4__ drev_context_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SVN_ERR_RA_NOT_IMPLEMENTED ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_4__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  create_getdrev_body ; 
 int /*<<< orphan*/  getdrev_closed ; 
 int /*<<< orphan*/  getdrev_ttable ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * svn_ra_serf__context_run_one (TYPE_3__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_ra_serf__create_expat_handler (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_ra_serf__get_stable_url (char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_ra_serf__xml_context_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_ra_serf__get_deleted_rev(svn_ra_session_t *session,
                             const char *path,
                             svn_revnum_t peg_revision,
                             svn_revnum_t end_revision,
                             svn_revnum_t *revision_deleted,
                             apr_pool_t *pool)
{
  drev_context_t *drev_ctx;
  svn_ra_serf__session_t *ras = session->priv;
  svn_ra_serf__handler_t *handler;
  svn_ra_serf__xml_context_t *xmlctx;
  const char *req_url;
  svn_error_t *err;

  drev_ctx = apr_pcalloc(pool, sizeof(*drev_ctx));
  drev_ctx->path = path;
  drev_ctx->peg_revision = peg_revision;
  drev_ctx->end_revision = end_revision;
  drev_ctx->revision_deleted = revision_deleted;

  SVN_ERR(svn_ra_serf__get_stable_url(&req_url, NULL /* latest_revnum */,
                                      ras, NULL /* url */, peg_revision,
                                      pool, pool));

  xmlctx = svn_ra_serf__xml_context_create(getdrev_ttable,
                                           NULL, getdrev_closed, NULL,
                                           drev_ctx,
                                           pool);
  handler = svn_ra_serf__create_expat_handler(ras, xmlctx, NULL, pool);

  handler->method = "REPORT";
  handler->path = req_url;
  handler->body_type = "text/xml";
  handler->body_delegate = create_getdrev_body;
  handler->body_delegate_baton = drev_ctx;

  err = svn_ra_serf__context_run_one(handler, pool);

  /* Map status 501: Method Not Implemented to our not implemented error.
     1.5.x servers and older don't support this report. */
  if (handler->sline.code == 501)
    return svn_error_createf(SVN_ERR_RA_NOT_IMPLEMENTED, err,
                             _("'%s' REPORT not implemented"),
                             "get-deleted-rev");
  SVN_ERR(err);

  return SVN_NO_ERROR;
}