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
struct TYPE_4__ {scalar_t__ kind; } ;
typedef  TYPE_1__ transaction_t ;
typedef  int /*<<< orphan*/  trail_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_TRANSACTION_DEAD ; 
 int /*<<< orphan*/  SVN_ERR_FS_TRANSACTION_NOT_DEAD ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_fs_bdb__get_txn (TYPE_1__**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ transaction_kind_dead ; 

__attribute__((used)) static svn_error_t *
get_txn(transaction_t **txn_p,
        svn_fs_t *fs,
        const char *txn_id,
        svn_boolean_t expect_dead,
        trail_t *trail,
        apr_pool_t *pool)
{
  transaction_t *txn;
  SVN_ERR(svn_fs_bdb__get_txn(&txn, fs, txn_id, trail, pool));
  if (expect_dead && (txn->kind != transaction_kind_dead))
    return svn_error_createf(SVN_ERR_FS_TRANSACTION_NOT_DEAD, 0,
                             _("Transaction is not dead: '%s'"), txn_id);
  if ((! expect_dead) && (txn->kind == transaction_kind_dead))
    return svn_error_createf(SVN_ERR_FS_TRANSACTION_DEAD, 0,
                             _("Transaction is dead: '%s'"), txn_id);
  *txn_p = txn;
  return SVN_NO_ERROR;
}