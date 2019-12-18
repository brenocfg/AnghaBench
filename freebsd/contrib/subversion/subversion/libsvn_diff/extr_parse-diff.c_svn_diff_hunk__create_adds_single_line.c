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
struct TYPE_4__ {int /*<<< orphan*/  reverse; } ;
typedef  TYPE_1__ svn_patch_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_diff_hunk_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  add_or_delete_single_line (int /*<<< orphan*/ **,char const*,TYPE_1__ const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_diff_hunk__create_adds_single_line(svn_diff_hunk_t **hunk_out,
                                       const char *line,
                                       const svn_patch_t *patch,
                                       apr_pool_t *result_pool,
                                       apr_pool_t *scratch_pool)
{
  SVN_ERR(add_or_delete_single_line(hunk_out, line, patch, 
                                    (!patch->reverse),
                                    result_pool, scratch_pool));
  return SVN_NO_ERROR;
}