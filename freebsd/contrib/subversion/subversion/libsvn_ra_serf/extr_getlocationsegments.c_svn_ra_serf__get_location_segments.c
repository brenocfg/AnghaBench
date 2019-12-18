#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  void* svn_revnum_t ;
struct TYPE_20__ {int /*<<< orphan*/ * priv; } ;
typedef  TYPE_2__ svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_ra_serf__xml_context_t ;
typedef  int /*<<< orphan*/  svn_ra_serf__session_t ;
struct TYPE_19__ {int code; } ;
struct TYPE_21__ {char* method; char const* path; char* body_type; TYPE_1__ sline; TYPE_5__* body_delegate_baton; int /*<<< orphan*/  body_delegate; } ;
typedef  TYPE_3__ svn_ra_serf__handler_t ;
typedef  int /*<<< orphan*/  svn_location_segment_receiver_t ;
struct TYPE_22__ {scalar_t__ apr_err; } ;
typedef  TYPE_4__ svn_error_t ;
struct TYPE_23__ {char const* path; void* receiver_baton; int /*<<< orphan*/  receiver; void* end_rev; void* start_rev; void* peg_revision; } ;
typedef  TYPE_5__ gls_context_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_RA_NOT_IMPLEMENTED ; 
 scalar_t__ SVN_ERR_UNSUPPORTED_FEATURE ; 
 TYPE_5__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  create_gls_body ; 
 int /*<<< orphan*/  gls_closed ; 
 int /*<<< orphan*/  gls_ttable ; 
 TYPE_4__* svn_error_create (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *) ; 
 TYPE_4__* svn_error_trace (TYPE_4__*) ; 
 TYPE_4__* svn_ra_serf__context_run_one (TYPE_3__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_ra_serf__create_expat_handler (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_serf__get_stable_url (char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* svn_ra_serf__unexpected_status (TYPE_3__*) ; 
 int /*<<< orphan*/ * svn_ra_serf__xml_context_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_ra_serf__get_location_segments(svn_ra_session_t *ra_session,
                                   const char *path,
                                   svn_revnum_t peg_revision,
                                   svn_revnum_t start_rev,
                                   svn_revnum_t end_rev,
                                   svn_location_segment_receiver_t receiver,
                                   void *receiver_baton,
                                   apr_pool_t *pool)
{
  gls_context_t *gls_ctx;
  svn_ra_serf__session_t *session = ra_session->priv;
  svn_ra_serf__handler_t *handler;
  svn_ra_serf__xml_context_t *xmlctx;
  const char *req_url;
  svn_error_t *err;

  gls_ctx = apr_pcalloc(pool, sizeof(*gls_ctx));
  gls_ctx->path = path;
  gls_ctx->peg_revision = peg_revision;
  gls_ctx->start_rev = start_rev;
  gls_ctx->end_rev = end_rev;
  gls_ctx->receiver = receiver;
  gls_ctx->receiver_baton = receiver_baton;

  SVN_ERR(svn_ra_serf__get_stable_url(&req_url, NULL /* latest_revnum */,
                                      session, NULL /* url */, peg_revision,
                                      pool, pool));

  xmlctx = svn_ra_serf__xml_context_create(gls_ttable,
                                           NULL, gls_closed, NULL,
                                           gls_ctx,
                                           pool);
  handler = svn_ra_serf__create_expat_handler(session, xmlctx, NULL, pool);

  handler->method = "REPORT";
  handler->path = req_url;
  handler->body_delegate = create_gls_body;
  handler->body_delegate_baton = gls_ctx;
  handler->body_type = "text/xml";

  err = svn_ra_serf__context_run_one(handler, pool);

  if (!err && handler->sline.code != 200)
    err = svn_ra_serf__unexpected_status(handler);

  if (err && (err->apr_err == SVN_ERR_UNSUPPORTED_FEATURE))
    return svn_error_create(SVN_ERR_RA_NOT_IMPLEMENTED, err, NULL);

  return svn_error_trace(err);
}