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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char* svn_dirent_basename (char const*,int /*<<< orphan*/ *) ; 
 char* svn_dirent_join (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_check_resolved_path (char const*,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 
 char* svn_uri_basename (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
append_basename_if_dir(const char **appendable_dirent_p,
                       const char *basename_of,
                       svn_boolean_t is_uri,
                       apr_pool_t *pool)
{
  svn_node_kind_t local_kind;
  SVN_ERR(svn_io_check_resolved_path(*appendable_dirent_p, &local_kind, pool));
  if (local_kind == svn_node_dir)
    {
      const char *base_name;

      if (is_uri)
        base_name = svn_uri_basename(basename_of, pool);
      else
        base_name = svn_dirent_basename(basename_of, NULL);

      *appendable_dirent_p = svn_dirent_join(*appendable_dirent_p,
                                             base_name, pool);
    }

  return SVN_NO_ERROR;
}