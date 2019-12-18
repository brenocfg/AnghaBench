#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_ra_serf__xml_context_t ;
typedef  int /*<<< orphan*/  svn_ra_serf__session_t ;
struct TYPE_13__ {char* method; char const* path; char* body_type; TYPE_4__* header_delegate_baton; int /*<<< orphan*/  header_delegate; int /*<<< orphan*/  custom_accept_encoding; int /*<<< orphan*/  body_delegate_baton; int /*<<< orphan*/  body_delegate; } ;
typedef  TYPE_3__ svn_ra_serf__handler_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_14__ {int /*<<< orphan*/  editor_baton; TYPE_1__* editor; int /*<<< orphan*/  body; int /*<<< orphan*/  body_template; int /*<<< orphan*/ * sess; } ;
typedef  TYPE_4__ report_context_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_11__ {int /*<<< orphan*/ * (* abort_edit ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * process_editor_report (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_update_report_headers ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_compose_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_ra_serf__create_expat_handler (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_serf__report_resource (char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_serf__request_body_get_delegate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_ra_serf__request_create (TYPE_3__*) ; 
 int /*<<< orphan*/ * svn_ra_serf__xml_context_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_xml_make_close_tag (TYPE_2__**,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  update_cdata ; 
 int /*<<< orphan*/  update_closed ; 
 int /*<<< orphan*/  update_opened ; 
 int /*<<< orphan*/  update_ttable ; 

__attribute__((used)) static svn_error_t *
finish_report(void *report_baton,
              apr_pool_t *pool)
{
  report_context_t *report = report_baton;
  svn_ra_serf__session_t *sess = report->sess;
  svn_ra_serf__handler_t *handler;
  svn_ra_serf__xml_context_t *xmlctx;
  const char *report_target;
  svn_stringbuf_t *buf = NULL;
  apr_pool_t *scratch_pool = svn_pool_create(pool);
  svn_error_t *err;

  svn_xml_make_close_tag(&buf, scratch_pool, "S:update-report");
  SVN_ERR(svn_stream_write(report->body_template, buf->data, &buf->len));
  SVN_ERR(svn_stream_close(report->body_template));

  SVN_ERR(svn_ra_serf__report_resource(&report_target, sess,  scratch_pool));

  xmlctx = svn_ra_serf__xml_context_create(update_ttable,
                                           update_opened, update_closed,
                                           update_cdata,
                                           report,
                                           scratch_pool);
  handler = svn_ra_serf__create_expat_handler(sess, xmlctx, NULL,
                                              scratch_pool);

  svn_ra_serf__request_body_get_delegate(&handler->body_delegate,
                                         &handler->body_delegate_baton,
                                         report->body);
  handler->method = "REPORT";
  handler->path = report_target;
  handler->body_type = "text/xml";
  handler->custom_accept_encoding = TRUE;
  handler->header_delegate = setup_update_report_headers;
  handler->header_delegate_baton = report;

  svn_ra_serf__request_create(handler);

  err = process_editor_report(report, handler, scratch_pool);

  if (err)
    {
      err = svn_error_trace(err);
      err = svn_error_compose_create(
                err,
                svn_error_trace(
                    report->editor->abort_edit(report->editor_baton,
                                               scratch_pool)));
    }

  svn_pool_destroy(scratch_pool);

  return svn_error_trace(err);
}