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
typedef  scalar_t__ svn_depth_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_VA_NULL ; 
 char const* apr_pstrcat (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_depth_to_word (scalar_t__) ; 
 scalar_t__ svn_depth_unknown ; 

__attribute__((used)) static const char *
log_depth(svn_depth_t depth, apr_pool_t *pool)
{
  if (depth == svn_depth_unknown)
    return "";
  return apr_pstrcat(pool, " depth=", svn_depth_to_word(depth), SVN_VA_NULL);
}