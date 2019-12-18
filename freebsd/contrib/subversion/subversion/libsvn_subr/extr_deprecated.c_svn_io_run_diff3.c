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
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_run_diff3_2 (int*,char const*,char const*,char const*,char const*,char const*,char const*,char const*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_io_run_diff3(const char *dir,
                 const char *mine,
                 const char *older,
                 const char *yours,
                 const char *mine_label,
                 const char *older_label,
                 const char *yours_label,
                 apr_file_t *merged,
                 int *exitcode,
                 const char *diff3_cmd,
                 apr_pool_t *pool)
{
  return svn_error_trace(svn_io_run_diff3_2(exitcode, dir, mine, older, yours,
                                            mine_label, older_label,
                                            yours_label,
                                            merged, diff3_cmd, NULL, pool));
}