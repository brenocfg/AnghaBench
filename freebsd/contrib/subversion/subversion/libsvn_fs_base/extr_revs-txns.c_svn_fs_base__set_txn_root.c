#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ kind; int /*<<< orphan*/  const* root_id; } ;
typedef  TYPE_1__ transaction_t ;
typedef  int /*<<< orphan*/  trail_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_id_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  get_txn (TYPE_1__**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_txn (int /*<<< orphan*/ *,TYPE_1__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_base__err_txn_not_mutable (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_fs_base__id_eq (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 scalar_t__ transaction_kind_normal ; 

svn_error_t *
svn_fs_base__set_txn_root(svn_fs_t *fs,
                          const char *txn_name,
                          const svn_fs_id_t *new_id,
                          trail_t *trail,
                          apr_pool_t *pool)
{
  transaction_t *txn;

  SVN_ERR(get_txn(&txn, fs, txn_name, FALSE, trail, pool));
  if (txn->kind != transaction_kind_normal)
    return svn_fs_base__err_txn_not_mutable(fs, txn_name);

  if (! svn_fs_base__id_eq(txn->root_id, new_id))
    {
      txn->root_id = new_id;
      SVN_ERR(put_txn(fs, txn, txn_name, trail, pool));
    }
  return SVN_NO_ERROR;
}