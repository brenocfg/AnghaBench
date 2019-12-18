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
typedef  int /*<<< orphan*/  svn_diff_t ;
struct file_merge_baton {int /*<<< orphan*/  scratch_pool; int /*<<< orphan*/  config; int /*<<< orphan*/  editor_cmd; int /*<<< orphan*/  current_line_latest; int /*<<< orphan*/  current_line_modified; int /*<<< orphan*/  latest_file; int /*<<< orphan*/  modified_file; int /*<<< orphan*/  merged_file; scalar_t__ abort_merge; int /*<<< orphan*/  remains_in_conflict; } ;
typedef  int /*<<< orphan*/  apr_off_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  merge_file_chunks (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
file_merge_output_conflict(void *output_baton,
                           apr_off_t original_start,
                           apr_off_t original_length,
                           apr_off_t modified_start,
                           apr_off_t modified_length,
                           apr_off_t latest_start,
                           apr_off_t latest_length,
                           svn_diff_t *resolved_diff)
{
  struct file_merge_baton *b = output_baton;

  if (b->abort_merge)
    return SVN_NO_ERROR;

  SVN_ERR(merge_file_chunks(&b->remains_in_conflict,
                            &b->abort_merge,
                            b->merged_file,
                            b->modified_file,
                            b->latest_file,
                            modified_start,
                            modified_length,
                            latest_start,
                            latest_length,
                            &b->current_line_modified,
                            &b->current_line_latest,
                            b->editor_cmd,
                            b->config,
                            b->scratch_pool));
  return SVN_NO_ERROR;
}