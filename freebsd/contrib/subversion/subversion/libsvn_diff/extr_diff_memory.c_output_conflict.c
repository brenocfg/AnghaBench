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
struct TYPE_4__ {scalar_t__ conflict_style; int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/  cancel_func; } ;
typedef  TYPE_1__ merge_output_baton_t ;
typedef  int /*<<< orphan*/  apr_off_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_MALFUNCTION () ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  merge_output_vtable ; 
 int /*<<< orphan*/  output_merge_marker (TYPE_1__*,int) ; 
 int /*<<< orphan*/  output_merge_token_range (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ svn_diff_conflict_display_latest ; 
 scalar_t__ svn_diff_conflict_display_modified ; 
 scalar_t__ svn_diff_conflict_display_modified_latest ; 
 scalar_t__ svn_diff_conflict_display_modified_original_latest ; 
 scalar_t__ svn_diff_conflict_display_resolved_modified_latest ; 
 int /*<<< orphan*/ * svn_diff_output2 (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
output_conflict(void *baton,
                apr_off_t original_start, apr_off_t original_length,
                apr_off_t modified_start, apr_off_t modified_length,
                apr_off_t latest_start, apr_off_t latest_length,
                svn_diff_t *diff)
{
  merge_output_baton_t *btn = baton;

  svn_diff_conflict_display_style_t style = btn->conflict_style;

  if (style == svn_diff_conflict_display_resolved_modified_latest)
    {
      if (diff)
        return svn_diff_output2(diff, baton, &merge_output_vtable,
                                btn->cancel_func, btn->cancel_baton);
      else
        style = svn_diff_conflict_display_modified_latest;
    }

  if (style == svn_diff_conflict_display_modified_latest ||
      style == svn_diff_conflict_display_modified_original_latest)
    {
      SVN_ERR(output_merge_marker(btn, 1/*modified*/));
      SVN_ERR(output_merge_token_range(btn, 1/*modified*/,
                                       modified_start, modified_length));

      if (style == svn_diff_conflict_display_modified_original_latest)
        {
          SVN_ERR(output_merge_marker(btn, 0/*original*/));
          SVN_ERR(output_merge_token_range(btn, 0/*original*/,
                                           original_start, original_length));
        }

      SVN_ERR(output_merge_marker(btn, 2/*separator*/));
      SVN_ERR(output_merge_token_range(btn, 2/*latest*/,
                                       latest_start, latest_length));
      SVN_ERR(output_merge_marker(btn, 3/*latest (end)*/));
    }
  else if (style == svn_diff_conflict_display_modified)
      SVN_ERR(output_merge_token_range(btn, 1/*modified*/,
                                       modified_start, modified_length));
  else if (style == svn_diff_conflict_display_latest)
      SVN_ERR(output_merge_token_range(btn, 2/*latest*/,
                                       latest_start, latest_length));
  else /* unknown style */
    SVN_ERR_MALFUNCTION();

  return SVN_NO_ERROR;
}