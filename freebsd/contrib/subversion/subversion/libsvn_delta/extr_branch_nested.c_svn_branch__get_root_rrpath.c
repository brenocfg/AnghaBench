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
typedef  int /*<<< orphan*/  svn_branch__state_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_ASSERT_NO_RETURN (char const*) ; 
 int /*<<< orphan*/  svn_branch__get_outer_branch_and_eid (int /*<<< orphan*/ **,int*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 char* svn_branch__get_rrpath_by_eid (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

const char *
svn_branch__get_root_rrpath(const svn_branch__state_t *branch,
                            apr_pool_t *result_pool)
{
  svn_branch__state_t *outer_branch;
  int outer_eid;
  const char *root_rrpath;

  svn_branch__get_outer_branch_and_eid(&outer_branch, &outer_eid, branch,
                                       result_pool);
  if (outer_branch)
    {
      root_rrpath
        = svn_branch__get_rrpath_by_eid(outer_branch, outer_eid, result_pool);
    }
  else
    {
      root_rrpath = "";
    }

  SVN_ERR_ASSERT_NO_RETURN(root_rrpath);
  return root_rrpath;
}