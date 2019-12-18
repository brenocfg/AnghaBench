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
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 char const* OP_FILE_COPY_TRANSLATED ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_WC_PATH_NOT_FOUND ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  svn_dirent_is_absolute (char const*) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_check_path (char const*,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_none ; 
 int /*<<< orphan*/ * svn_skel__make_empty_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_skel__prepend_str (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_to_relpath (char const**,int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__wq_build_file_copy_translated(svn_skel_t **work_item,
                                      svn_wc__db_t *db,
                                      const char *local_abspath,
                                      const char *src_abspath,
                                      const char *dst_abspath,
                                      apr_pool_t *result_pool,
                                      apr_pool_t *scratch_pool)
{
  svn_node_kind_t kind;
  const char *local_relpath;

  *work_item = svn_skel__make_empty_list(result_pool);

  SVN_ERR_ASSERT(svn_dirent_is_absolute(local_abspath));
  SVN_ERR_ASSERT(svn_dirent_is_absolute(src_abspath));
  SVN_ERR_ASSERT(svn_dirent_is_absolute(dst_abspath));

  /* File must exist */
  SVN_ERR(svn_io_check_path(src_abspath, &kind, result_pool));

  if (kind == svn_node_none)
    return svn_error_createf(SVN_ERR_WC_PATH_NOT_FOUND, NULL,
                             _("'%s' not found"),
                             svn_dirent_local_style(src_abspath,
                                                    scratch_pool));

  SVN_ERR(svn_wc__db_to_relpath(&local_relpath, db, local_abspath, dst_abspath,
                                result_pool, scratch_pool));
  svn_skel__prepend_str(local_relpath, *work_item, result_pool);

  SVN_ERR(svn_wc__db_to_relpath(&local_relpath, db, local_abspath, src_abspath,
                                result_pool, scratch_pool));
  svn_skel__prepend_str(local_relpath, *work_item, result_pool);

  SVN_ERR(svn_wc__db_to_relpath(&local_relpath, db, local_abspath,
                                local_abspath, result_pool, scratch_pool));
  svn_skel__prepend_str(local_relpath, *work_item, result_pool);

  svn_skel__prepend_str(OP_FILE_COPY_TRANSLATED, *work_item, result_pool);

  return SVN_NO_ERROR;
}