#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  void* svn_revnum_t ;
struct TYPE_14__ {TYPE_4__* priv; } ;
typedef  TYPE_3__ svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_ra_serf__xml_context_t ;
struct TYPE_12__ {int /*<<< orphan*/  path; } ;
struct TYPE_15__ {TYPE_1__ session_url; } ;
typedef  TYPE_4__ svn_ra_serf__session_t ;
struct TYPE_13__ {int code; } ;
struct TYPE_16__ {char* method; char* body_type; TYPE_2__ sline; struct revision_report_t* body_delegate_baton; int /*<<< orphan*/  body_delegate; int /*<<< orphan*/  path; } ;
typedef  TYPE_5__ svn_ra_serf__handler_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_delta_editor_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct revision_report_t {int /*<<< orphan*/  rev_props; int /*<<< orphan*/  send_deltas; void* low_water_mark; void* revision; int /*<<< orphan*/  done; void* editor_baton; int /*<<< orphan*/  const* editor; int /*<<< orphan*/  pool; int /*<<< orphan*/ * member_0; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  create_replay_body ; 
 int /*<<< orphan*/  replay_cdata ; 
 int /*<<< orphan*/  replay_closed ; 
 int /*<<< orphan*/  replay_opened ; 
 int /*<<< orphan*/  replay_ttable ; 
 int /*<<< orphan*/  svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_serf__context_run_one (TYPE_5__*,int /*<<< orphan*/ *) ; 
 TYPE_5__* svn_ra_serf__create_expat_handler (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_serf__report_resource (char const**,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_serf__unexpected_status (TYPE_5__*) ; 
 int /*<<< orphan*/ * svn_ra_serf__xml_context_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct revision_report_t*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_ra_serf__replay(svn_ra_session_t *ra_session,
                    svn_revnum_t revision,
                    svn_revnum_t low_water_mark,
                    svn_boolean_t send_deltas,
                    const svn_delta_editor_t *editor,
                    void *edit_baton,
                    apr_pool_t *scratch_pool)
{
  struct revision_report_t ctx = { NULL };
  svn_ra_serf__session_t *session = ra_session->priv;
  svn_ra_serf__handler_t *handler;
  svn_ra_serf__xml_context_t *xmlctx;
  const char *report_target;

  SVN_ERR(svn_ra_serf__report_resource(&report_target, session,
                                       scratch_pool));

  ctx.pool = svn_pool_create(scratch_pool);
  ctx.editor = editor;
  ctx.editor_baton = edit_baton;
  ctx.done = FALSE;
  ctx.revision = revision;
  ctx.low_water_mark = low_water_mark;
  ctx.send_deltas = send_deltas;
  ctx.rev_props = apr_hash_make(scratch_pool);

  xmlctx = svn_ra_serf__xml_context_create(replay_ttable,
                                           replay_opened, replay_closed,
                                           replay_cdata,
                                           &ctx,
                                           scratch_pool);

  handler = svn_ra_serf__create_expat_handler(session, xmlctx, NULL,
                                              scratch_pool);

  handler->method = "REPORT";
  handler->path = session->session_url.path;
  handler->body_delegate = create_replay_body;
  handler->body_delegate_baton = &ctx;
  handler->body_type = "text/xml";

  /* Not setting up done handler as we don't use a global context */

  SVN_ERR(svn_ra_serf__context_run_one(handler, scratch_pool));

  if (handler->sline.code != 200)
    SVN_ERR(svn_ra_serf__unexpected_status(handler));

  return SVN_NO_ERROR;
}