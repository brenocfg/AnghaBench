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
typedef  int svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_file_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_io_run_diff3_3 (int*,char*,char const*,char const*,char const*,char const*,char const*,char const*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
do_text_merge_external(svn_boolean_t *contains_conflicts,
                       apr_file_t *result_f,
                       const char *diff3_cmd,
                       const apr_array_header_t *merge_options,
                       const char *detranslated_target,
                       const char *left_abspath,
                       const char *right_abspath,
                       const char *target_label,
                       const char *left_label,
                       const char *right_label,
                       apr_pool_t *scratch_pool)
{
  int exit_code;

  SVN_ERR(svn_io_run_diff3_3(&exit_code, ".",
                             detranslated_target, left_abspath, right_abspath,
                             target_label, left_label, right_label,
                             result_f, diff3_cmd,
                             merge_options, scratch_pool));

  *contains_conflicts = exit_code == 1;

  return SVN_NO_ERROR;
}