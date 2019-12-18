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
typedef  int svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_ILLEGAL_TARGET ; 
 int /*<<< orphan*/  SVN_ERR_NODE_UNEXPECTED_KIND ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 char const* svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,...) ; 
#define  svn_node_dir 129 
#define  svn_node_file 128 
 scalar_t__ svn_path_is_url (char const*) ; 
 int /*<<< orphan*/  svn_prop_is_known_svn_dir_prop (char const*) ; 
 int /*<<< orphan*/  svn_prop_is_known_svn_file_prop (char const*) ; 

__attribute__((used)) static svn_error_t *
validate_prop_against_node_kind(const char *name,
                                const char *path,
                                svn_node_kind_t node_kind,
                                apr_pool_t *pool)
{
  const char *path_display
    = svn_path_is_url(path) ? path : svn_dirent_local_style(path, pool);

  switch (node_kind)
    {
    case svn_node_dir:
      if (! svn_prop_is_known_svn_dir_prop(name)
          && svn_prop_is_known_svn_file_prop(name))
        return svn_error_createf(SVN_ERR_ILLEGAL_TARGET, NULL,
                                 _("Cannot set '%s' on a directory ('%s')"),
                                 name, path_display);
      break;
    case svn_node_file:
      if (! svn_prop_is_known_svn_file_prop(name)
          && svn_prop_is_known_svn_dir_prop(name))
        return svn_error_createf(SVN_ERR_ILLEGAL_TARGET, NULL,
                                 _("Cannot set '%s' on a file ('%s')"),
                                 name,
                                 path_display);
      break;
    default:
      return svn_error_createf(SVN_ERR_NODE_UNEXPECTED_KIND, NULL,
                               _("'%s' is not a file or directory"),
                               path_display);
    }

  return SVN_NO_ERROR;
}