#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  transaction_t ;
struct TYPE_13__ {int /*<<< orphan*/  db_txn; } ;
typedef  TYPE_1__ trail_t ;
struct TYPE_14__ {TYPE_3__* fsap_data; } ;
typedef  TYPE_2__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_15__ {TYPE_10__* transactions; } ;
typedef  TYPE_3__ base_fs_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_12__ {int /*<<< orphan*/  (* del ) (TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  DBT ;

/* Variables and functions */
 int /*<<< orphan*/ * BDB_WRAP (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  N_ (char*) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ is_committed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_fs_base__err_txn_not_mutable (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  svn_fs_base__str_to_dbt (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_fs_base__trail_debug (TYPE_1__*,char*,char*) ; 
 int /*<<< orphan*/  svn_fs_bdb__get_txn (int /*<<< orphan*/ **,TYPE_2__*,char const*,TYPE_1__*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_bdb__delete_txn(svn_fs_t *fs,
                       const char *txn_name,
                       trail_t *trail,
                       apr_pool_t *pool)
{
  base_fs_data_t *bfd = fs->fsap_data;
  DBT key;
  transaction_t *txn;

  /* Make sure TXN is dead. */
  SVN_ERR(svn_fs_bdb__get_txn(&txn, fs, txn_name, trail, pool));
  if (is_committed(txn))
    return svn_fs_base__err_txn_not_mutable(fs, txn_name);

  /* Delete the transaction from the `transactions' table. */
  svn_fs_base__str_to_dbt(&key, txn_name);
  svn_fs_base__trail_debug(trail, "transactions", "del");
  return BDB_WRAP(fs, N_("deleting entry from 'transactions' table"),
                  bfd->transactions->del(bfd->transactions,
                                         trail->db_txn, &key, 0));
}