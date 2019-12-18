#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_wc_notify_func2_t ;
struct TYPE_8__ {int /*<<< orphan*/  abspath; } ;
typedef  TYPE_1__ svn_wc__db_wcroot_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct op_delete_baton_t {char const* moved_to_relpath; int /*<<< orphan*/  notify; int /*<<< orphan*/  delete_dir_externals; int /*<<< orphan*/ * work_items; int /*<<< orphan*/ * conflict; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  STMT_FINALIZE_DELETE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_UNSUPPORTED_FEATURE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_WC__DB_WITH_TXN (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VERIFY_USABLE_WCROOT (TYPE_1__*) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  delete_node (struct op_delete_baton_t*,TYPE_1__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_delete_notify ; 
 int /*<<< orphan*/  flush_entries (TYPE_1__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  op_delete_txn ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_depth_infinity ; 
 int /*<<< orphan*/  svn_dirent_is_absolute (char const*) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_wc__db_wcroot_parse_local_abspath (TYPE_1__**,char const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  with_finalization (TYPE_1__*,char const*,int /*<<< orphan*/ ,struct op_delete_baton_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,scalar_t__,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__db_op_delete(svn_wc__db_t *db,
                     const char *local_abspath,
                     const char *moved_to_abspath,
                     svn_boolean_t delete_dir_externals,
                     svn_skel_t *conflict,
                     svn_skel_t *work_items,
                     svn_cancel_func_t cancel_func,
                     void *cancel_baton,
                     svn_wc_notify_func2_t notify_func,
                     void *notify_baton,
                     apr_pool_t *scratch_pool)
{
  svn_wc__db_wcroot_t *wcroot;
  svn_wc__db_wcroot_t *moved_to_wcroot;
  const char *local_relpath;
  const char *moved_to_relpath;
  struct op_delete_baton_t odb;

  SVN_ERR_ASSERT(svn_dirent_is_absolute(local_abspath));

  SVN_ERR(svn_wc__db_wcroot_parse_local_abspath(&wcroot, &local_relpath,
                                                db, local_abspath,
                                                scratch_pool, scratch_pool));
  VERIFY_USABLE_WCROOT(wcroot);

  if (moved_to_abspath)
    {
      SVN_ERR(svn_wc__db_wcroot_parse_local_abspath(&moved_to_wcroot,
                                                    &moved_to_relpath,
                                                    db, moved_to_abspath,
                                                    scratch_pool,
                                                    scratch_pool));
      VERIFY_USABLE_WCROOT(moved_to_wcroot);

      if (strcmp(wcroot->abspath, moved_to_wcroot->abspath) != 0)
        return svn_error_createf(SVN_ERR_UNSUPPORTED_FEATURE, NULL,
                                 _("Cannot move '%s' to '%s' because they "
                                   "are not in the same working copy"),
                                 svn_dirent_local_style(local_abspath,
                                                        scratch_pool),
                                 svn_dirent_local_style(moved_to_abspath,
                                                        scratch_pool));
    }
  else
    moved_to_relpath = NULL;

  odb.moved_to_relpath = moved_to_relpath;
  odb.conflict = conflict;
  odb.work_items = work_items;
  odb.delete_dir_externals = delete_dir_externals;

  if (notify_func)
    {
      /* Perform the deletion operation (transactionally), perform any
         notifications necessary, and then clean out our temporary tables.  */
      odb.notify = TRUE;
      SVN_ERR(with_finalization(wcroot, local_relpath,
                                op_delete_txn, &odb,
                                do_delete_notify, NULL,
                                cancel_func, cancel_baton,
                                notify_func, notify_baton,
                                STMT_FINALIZE_DELETE,
                                scratch_pool));
    }
  else
    {
      /* Avoid the trigger work */
      odb.notify = FALSE;
      SVN_WC__DB_WITH_TXN(
                    delete_node(&odb, wcroot, local_relpath, scratch_pool),
                    wcroot);
    }

  SVN_ERR(flush_entries(wcroot, local_abspath, svn_depth_infinity,
                        scratch_pool));

  return SVN_NO_ERROR;
}