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
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_fs_txn_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_editor_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int /*<<< orphan*/  apr_uint32_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_editor (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_begin_txn2 (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_txn_name (char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_youngest_rev (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs__editor_create(svn_editor_t **editor,
                      const char **txn_name,
                      svn_fs_t *fs,
                      apr_uint32_t flags,
                      svn_cancel_func_t cancel_func,
                      void *cancel_baton,
                      apr_pool_t *result_pool,
                      apr_pool_t *scratch_pool)
{
  svn_revnum_t revision;
  svn_fs_txn_t *txn;

  SVN_ERR(svn_fs_youngest_rev(&revision, fs, scratch_pool));
  SVN_ERR(svn_fs_begin_txn2(&txn, fs, revision, flags, result_pool));
  SVN_ERR(svn_fs_txn_name(txn_name, txn, result_pool));
  return svn_error_trace(make_editor(editor, txn,
                                     cancel_func, cancel_baton,
                                     result_pool, scratch_pool));
}