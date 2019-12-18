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
typedef  int /*<<< orphan*/  svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_PROP_MERGEINFO ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_fs_change_node_prop (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos__validate_prop (char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verify_mergeinfo (int /*<<< orphan*/  const*,char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_repos_fs_change_node_prop(svn_fs_root_t *root,
                              const char *path,
                              const char *name,
                              const svn_string_t *value,
                              apr_pool_t *pool)
{
  if (value && strcmp(name, SVN_PROP_MERGEINFO) == 0)
    SVN_ERR(verify_mergeinfo(value, path, pool));

  /* Validate the property, then call the wrapped function. */
  SVN_ERR(svn_repos__validate_prop(name, value, pool));
  return svn_fs_change_node_prop(root, path, name, value, pool);
}