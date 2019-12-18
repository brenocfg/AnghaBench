#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_WC_NOT_SYMLINK ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* svn_dirent_canonicalize (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_dirname (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_get_absolute (char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_is_absolute (char const*) ; 
 char* svn_dirent_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_read_link (TYPE_1__**,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_path_is_backpath_present (char const*) ; 

__attribute__((used)) static svn_error_t *
read_link_target(const char **link_target_abspath,
                 const char *local_abspath,
                 apr_pool_t *pool)
{
  svn_string_t *link_target;
  const char *canon_link_target;

  SVN_ERR(svn_io_read_link(&link_target, local_abspath, pool));
  if (link_target->len == 0)
    return svn_error_createf(SVN_ERR_WC_NOT_SYMLINK, NULL,
                             _("The symlink at '%s' points nowhere"),
                             svn_dirent_local_style(local_abspath, pool));

  canon_link_target = svn_dirent_canonicalize(link_target->data, pool);

  /* Treat relative symlinks as relative to LOCAL_ABSPATH's parent. */
  if (!svn_dirent_is_absolute(canon_link_target))
    canon_link_target = svn_dirent_join(svn_dirent_dirname(local_abspath,
                                                           pool),
                                        canon_link_target, pool);

  /* Collapse any .. in the symlink part of the path. */
  if (svn_path_is_backpath_present(canon_link_target))
    SVN_ERR(svn_dirent_get_absolute(link_target_abspath, canon_link_target,
                                    pool));
  else
    *link_target_abspath = canon_link_target;

  return SVN_NO_ERROR;
}