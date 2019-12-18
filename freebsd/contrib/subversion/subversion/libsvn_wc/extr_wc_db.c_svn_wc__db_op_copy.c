#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct op_copy_baton {TYPE_1__* src_wcroot; TYPE_1__* dst_wcroot; int /*<<< orphan*/  dst_op_root_relpath; int /*<<< orphan*/  is_move; int /*<<< orphan*/  const* work_items; int /*<<< orphan*/  dst_relpath; int /*<<< orphan*/  src_relpath; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_5__ {int /*<<< orphan*/  abspath; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_WC__DB_WITH_TXN (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  VERIFY_USABLE_WCROOT (TYPE_1__*) ; 
 int /*<<< orphan*/  op_copy_txn (TYPE_1__*,struct op_copy_baton*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_is_absolute (char const*) ; 
 int /*<<< orphan*/  svn_dirent_skip_ancestor (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_wc__db_wcroot_parse_local_abspath (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__db_op_copy(svn_wc__db_t *db,
                   const char *src_abspath,
                   const char *dst_abspath,
                   const char *dst_op_root_abspath,
                   svn_boolean_t is_move,
                   const svn_skel_t *work_items,
                   apr_pool_t *scratch_pool)
{
  struct op_copy_baton ocb = {0};

  SVN_ERR_ASSERT(svn_dirent_is_absolute(src_abspath));
  SVN_ERR_ASSERT(svn_dirent_is_absolute(dst_abspath));
  SVN_ERR_ASSERT(svn_dirent_is_absolute(dst_op_root_abspath));

  SVN_ERR(svn_wc__db_wcroot_parse_local_abspath(&ocb.src_wcroot,
                                                &ocb.src_relpath, db,
                                                src_abspath,
                                                scratch_pool, scratch_pool));
  VERIFY_USABLE_WCROOT(ocb.src_wcroot);

  SVN_ERR(svn_wc__db_wcroot_parse_local_abspath(&ocb.dst_wcroot,
                                                &ocb.dst_relpath,
                                                db, dst_abspath,
                                                scratch_pool, scratch_pool));
  VERIFY_USABLE_WCROOT(ocb.dst_wcroot);

  ocb.work_items = work_items;
  ocb.is_move = is_move;
  ocb.dst_op_root_relpath = svn_dirent_skip_ancestor(ocb.dst_wcroot->abspath,
                                                     dst_op_root_abspath);

  /* Call with the sdb in src_wcroot. It might call itself again to
     also obtain a lock in dst_wcroot */
  SVN_WC__DB_WITH_TXN(op_copy_txn(ocb.src_wcroot, &ocb, scratch_pool),
                      ocb.src_wcroot);

  return SVN_NO_ERROR;
}