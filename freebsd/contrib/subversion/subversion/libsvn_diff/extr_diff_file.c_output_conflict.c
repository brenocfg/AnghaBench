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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_diff_t ;
typedef  scalar_t__ svn_diff_conflict_display_style_t ;
struct TYPE_4__ {scalar_t__ conflict_style; int /*<<< orphan*/  conflict_latest; int /*<<< orphan*/  output_stream; int /*<<< orphan*/  conflict_separator; int /*<<< orphan*/  conflict_original; int /*<<< orphan*/  conflict_modified; int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/  cancel_func; } ;
typedef  TYPE_1__ svn_diff3__file_output_baton_t ;
typedef  int /*<<< orphan*/  apr_off_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_MALFUNCTION () ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * output_conflict_with_context (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_hunk (void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_marker_eol (TYPE_1__*) ; 
 int /*<<< orphan*/  svn_diff3__file_output_vtable ; 
 scalar_t__ svn_diff_conflict_display_latest ; 
 scalar_t__ svn_diff_conflict_display_modified ; 
 scalar_t__ svn_diff_conflict_display_modified_latest ; 
 scalar_t__ svn_diff_conflict_display_modified_original_latest ; 
 scalar_t__ svn_diff_conflict_display_only_conflicts ; 
 scalar_t__ svn_diff_conflict_display_resolved_modified_latest ; 
 int /*<<< orphan*/ * svn_diff_output2 (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_puts (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
output_conflict(void *baton,
                apr_off_t original_start, apr_off_t original_length,
                apr_off_t modified_start, apr_off_t modified_length,
                apr_off_t latest_start, apr_off_t latest_length,
                svn_diff_t *diff)
{
  svn_diff3__file_output_baton_t *file_baton = baton;

  svn_diff_conflict_display_style_t style = file_baton->conflict_style;

  if (style == svn_diff_conflict_display_only_conflicts)
    return output_conflict_with_context(file_baton,
                                        original_start, original_length,
                                        modified_start, modified_length,
                                        latest_start, latest_length);

  if (style == svn_diff_conflict_display_resolved_modified_latest)
    {
      if (diff)
        return svn_diff_output2(diff, baton,
                                &svn_diff3__file_output_vtable,
                                file_baton->cancel_func,
                                file_baton->cancel_baton);
      else
        style = svn_diff_conflict_display_modified_latest;
    }

  if (style == svn_diff_conflict_display_modified_latest ||
      style == svn_diff_conflict_display_modified_original_latest)
    {
      SVN_ERR(svn_stream_puts(file_baton->output_stream,
                               file_baton->conflict_modified));
      SVN_ERR(output_marker_eol(file_baton));

      SVN_ERR(output_hunk(baton, 1, modified_start, modified_length));

      if (style == svn_diff_conflict_display_modified_original_latest)
        {
          SVN_ERR(svn_stream_puts(file_baton->output_stream,
                                   file_baton->conflict_original));
          SVN_ERR(output_marker_eol(file_baton));
          SVN_ERR(output_hunk(baton, 0, original_start, original_length));
        }

      SVN_ERR(svn_stream_puts(file_baton->output_stream,
                              file_baton->conflict_separator));
      SVN_ERR(output_marker_eol(file_baton));

      SVN_ERR(output_hunk(baton, 2, latest_start, latest_length));

      SVN_ERR(svn_stream_puts(file_baton->output_stream,
                              file_baton->conflict_latest));
      SVN_ERR(output_marker_eol(file_baton));
    }
  else if (style == svn_diff_conflict_display_modified)
    SVN_ERR(output_hunk(baton, 1, modified_start, modified_length));
  else if (style == svn_diff_conflict_display_latest)
    SVN_ERR(output_hunk(baton, 2, latest_start, latest_length));
  else /* unknown style */
    SVN_ERR_MALFUNCTION();

  return SVN_NO_ERROR;
}