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
struct TYPE_4__ {scalar_t__ bid; } ;
typedef  TYPE_1__ svn_branch__state_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 char* apr_psprintf (int /*<<< orphan*/ *,char*,int) ; 
 int atoi (scalar_t__) ; 
 char* svn_branch__get_root_rrpath (TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 char const* svn_relpath_join (char const*,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *
branch_get_storage_root_rrpath(const svn_branch__state_t *branch,
                               apr_pool_t *result_pool)
{
  int top_branch_num = atoi(branch->bid + 1);
  const char *top_path = apr_psprintf(result_pool, "top%d", top_branch_num);
  const char *nested_path = svn_branch__get_root_rrpath(branch, result_pool);

  return svn_relpath_join(top_path, nested_path, result_pool);
}