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
 int /*<<< orphan*/  branch_get_storage_root_rrpath (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 char* svn_branch__get_path_by_eid (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *) ; 
 char* svn_relpath_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *
branch_get_storage_rrpath_by_eid(const svn_branch__state_t *branch,
                                 int eid,
                                 apr_pool_t *result_pool)
{
  const char *path = svn_branch__get_path_by_eid(branch, eid, result_pool);
  const char *rrpath = NULL;

  if (path)
    {
      rrpath = svn_relpath_join(branch_get_storage_root_rrpath(branch,
                                                               result_pool),
                                path, result_pool);
    }
  return rrpath;
}