#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct file_merge_baton {int /*<<< orphan*/  scratch_pool; int /*<<< orphan*/  current_line_latest; int /*<<< orphan*/  latest_file; int /*<<< orphan*/  merged_file; scalar_t__ abort_merge; } ;
typedef  int /*<<< orphan*/  apr_off_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  copy_to_merged_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
file_merge_output_diff_latest(void *output_baton,
                              apr_off_t original_start,
                              apr_off_t original_length,
                              apr_off_t modified_start,
                              apr_off_t modified_length,
                              apr_off_t latest_start,
                              apr_off_t latest_length)
{
  struct file_merge_baton *b = output_baton;

  if (b->abort_merge)
    return SVN_NO_ERROR;

  SVN_ERR(copy_to_merged_file(&b->current_line_latest,
                              b->merged_file,
                              b->latest_file,
                              latest_start,
                              latest_length,
                              b->current_line_latest,
                              b->scratch_pool));

  return SVN_NO_ERROR;
}