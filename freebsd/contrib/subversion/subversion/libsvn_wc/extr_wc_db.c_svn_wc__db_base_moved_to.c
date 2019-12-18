#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char const* abspath; } ;
typedef  TYPE_1__ svn_wc__db_wcroot_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_WC__DB_WITH_TXN (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  VERIFY_USABLE_WCROOT (TYPE_1__*) ; 
 int /*<<< orphan*/  svn_dirent_is_absolute (char const*) ; 
 char const* svn_dirent_join (char const*,char const*,int /*<<< orphan*/ *) ; 
 char const* svn_relpath_skip_ancestor (char const*,char const*) ; 
 int /*<<< orphan*/  svn_wc__db_scan_moved_to_internal (char const**,char const**,char const**,TYPE_1__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_wcroot_parse_local_abspath (TYPE_1__**,char const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__db_base_moved_to(const char **move_dst_abspath,
                         const char **move_dst_op_root_abspath,
                         const char **move_src_root_abspath,
                         const char **delete_abspath,
                         svn_wc__db_t *db,
                         const char *local_abspath,
                         apr_pool_t *result_pool,
                         apr_pool_t *scratch_pool)
{
  svn_wc__db_wcroot_t *wcroot;
  const char *local_relpath;
  const char *dst_root_relpath;
  const char *src_root_relpath, *delete_relpath;

  SVN_ERR_ASSERT(svn_dirent_is_absolute(local_abspath));


  SVN_ERR(svn_wc__db_wcroot_parse_local_abspath(&wcroot, &local_relpath, db,
                              local_abspath, scratch_pool, scratch_pool));
  VERIFY_USABLE_WCROOT(wcroot);

  SVN_WC__DB_WITH_TXN(svn_wc__db_scan_moved_to_internal(&src_root_relpath,
                                                        &dst_root_relpath,
                                                        &delete_relpath,
                                                        wcroot, local_relpath,
                                                        0 /* BASE */,
                                                        scratch_pool,
                                                        scratch_pool),
                      wcroot);

  if (move_dst_abspath)
    *move_dst_abspath =
        dst_root_relpath
          ? svn_dirent_join(wcroot->abspath,
                            svn_dirent_join(
                                    dst_root_relpath,
                                    svn_relpath_skip_ancestor(src_root_relpath,
                                                              local_relpath),
                                    scratch_pool),
                            result_pool)
          : NULL;

  if (move_dst_op_root_abspath)
    *move_dst_op_root_abspath =
          dst_root_relpath
              ? svn_dirent_join(wcroot->abspath, dst_root_relpath, result_pool)
              : NULL;

  if (move_src_root_abspath)
    *move_src_root_abspath =
          src_root_relpath
              ? svn_dirent_join(wcroot->abspath, src_root_relpath, result_pool)
              : NULL;

  if (delete_abspath)
    *delete_abspath =
          delete_relpath
              ? svn_dirent_join(wcroot->abspath, delete_relpath, result_pool)
              : NULL;

  return SVN_NO_ERROR;
}