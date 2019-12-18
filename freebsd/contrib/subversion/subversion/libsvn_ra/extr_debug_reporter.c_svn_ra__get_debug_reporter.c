#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stream_t ;
struct TYPE_4__ {int /*<<< orphan*/  abort_report; int /*<<< orphan*/  finish_report; int /*<<< orphan*/  link_path; int /*<<< orphan*/  delete_path; int /*<<< orphan*/  set_path; } ;
typedef  TYPE_1__ svn_ra_reporter3_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct report_baton {int /*<<< orphan*/ * out; void* wrapped_report_baton; TYPE_1__ const* wrapped_reporter; } ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  abort_report ; 
 scalar_t__ apr_file_open_stderr (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 void* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  delete_path ; 
 int /*<<< orphan*/  finish_report ; 
 int /*<<< orphan*/  link_path ; 
 int /*<<< orphan*/  set_path ; 
 int /*<<< orphan*/ * svn_error_wrap_apr (scalar_t__,char*) ; 
 int /*<<< orphan*/ * svn_stream_from_aprfile2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_ra__get_debug_reporter(const svn_ra_reporter3_t **reporter,
                           void **report_baton,
                           const svn_ra_reporter3_t *wrapped_reporter,
                           void *wrapped_report_baton,
                           apr_pool_t *pool)
{
  svn_ra_reporter3_t *tree_reporter;
  struct report_baton *rb;
  apr_file_t *errfp;
  svn_stream_t *out;

  apr_status_t apr_err = apr_file_open_stderr(&errfp, pool);
  if (apr_err)
    return svn_error_wrap_apr(apr_err, "Problem opening stderr");

  out = svn_stream_from_aprfile2(errfp, TRUE, pool);

  /* ### svn_delta_default_editor() */
  tree_reporter = apr_palloc(pool, sizeof(*tree_reporter));
  rb = apr_palloc(pool, sizeof(*rb));

  tree_reporter->set_path = set_path;
  tree_reporter->delete_path = delete_path;
  tree_reporter->link_path = link_path;
  tree_reporter->finish_report = finish_report;
  tree_reporter->abort_report = abort_report;

  rb->wrapped_reporter = wrapped_reporter;
  rb->wrapped_report_baton = wrapped_report_baton;
  rb->out = out;

  *reporter = tree_reporter;
  *report_baton = rb;

  return SVN_NO_ERROR;
}