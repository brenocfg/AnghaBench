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
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_diff_t ;
typedef  int /*<<< orphan*/  svn_diff_conflict_display_style_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  svn_diff_mem_string_output_merge3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,char const*,char const*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 

svn_error_t *
svn_diff_mem_string_output_merge2(svn_stream_t *output_stream,
                                  svn_diff_t *diff,
                                  const svn_string_t *original,
                                  const svn_string_t *modified,
                                  const svn_string_t *latest,
                                  const char *conflict_original,
                                  const char *conflict_modified,
                                  const char *conflict_latest,
                                  const char *conflict_separator,
                                  svn_diff_conflict_display_style_t style,
                                  apr_pool_t *pool)
{
  return svn_error_trace(svn_diff_mem_string_output_merge3(output_stream, diff,
                                                           original,
                                                           modified, latest,
                                                           conflict_original,
                                                           conflict_modified,
                                                           conflict_latest,
                                                           conflict_separator,
                                                           style,
                                                           /* no cancelation */
                                                           NULL, NULL,
                                                           pool));
}