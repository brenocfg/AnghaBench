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
struct TYPE_3__ {scalar_t__ prejfile; scalar_t__ conflict_wrk; scalar_t__ conflict_new; scalar_t__ conflict_old; } ;
typedef  TYPE_1__ svn_wc_entry_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char* svn_dirent_join (char const*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_check_path (char const*,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_file ; 

svn_error_t *
svn_wc_conflicted_p(svn_boolean_t *text_conflicted_p,
                    svn_boolean_t *prop_conflicted_p,
                    const char *dir_path,
                    const svn_wc_entry_t *entry,
                    apr_pool_t *pool)
{
  svn_node_kind_t kind;
  const char *path;

  *text_conflicted_p = FALSE;
  *prop_conflicted_p = FALSE;

  if (entry->conflict_old)
    {
      path = svn_dirent_join(dir_path, entry->conflict_old, pool);
      SVN_ERR(svn_io_check_path(path, &kind, pool));
      *text_conflicted_p = (kind == svn_node_file);
    }

  if ((! *text_conflicted_p) && (entry->conflict_new))
    {
      path = svn_dirent_join(dir_path, entry->conflict_new, pool);
      SVN_ERR(svn_io_check_path(path, &kind, pool));
      *text_conflicted_p = (kind == svn_node_file);
    }

  if ((! *text_conflicted_p) && (entry->conflict_wrk))
    {
      path = svn_dirent_join(dir_path, entry->conflict_wrk, pool);
      SVN_ERR(svn_io_check_path(path, &kind, pool));
      *text_conflicted_p = (kind == svn_node_file);
    }

  if (entry->prejfile)
    {
      path = svn_dirent_join(dir_path, entry->prejfile, pool);
      SVN_ERR(svn_io_check_path(path, &kind, pool));
      *prop_conflicted_p = (kind == svn_node_file);
    }

  return SVN_NO_ERROR;
}