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
typedef  scalar_t__ svn_node_kind_t ;
typedef  scalar_t__ svn_depth_t ;
typedef  int svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ strcmp (char const*,char const*) ; 
 scalar_t__ svn_depth_files ; 
 scalar_t__ svn_depth_immediates ; 
 scalar_t__ svn_depth_infinity ; 
 char* svn_dirent_dirname (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_file ; 

__attribute__((used)) static svn_boolean_t
depth_includes(const char *root_abspath,
               svn_depth_t depth,
               const char *child_abspath,
               svn_node_kind_t child_kind,
               apr_pool_t *scratch_pool)
{
  const char *parent_abspath = svn_dirent_dirname(child_abspath, scratch_pool);

  return (depth == svn_depth_infinity
          || ((depth == svn_depth_immediates
               || (depth == svn_depth_files && child_kind == svn_node_file))
              && strcmp(root_abspath, parent_abspath) == 0)
          || strcmp(root_abspath, child_abspath) == 0);
}