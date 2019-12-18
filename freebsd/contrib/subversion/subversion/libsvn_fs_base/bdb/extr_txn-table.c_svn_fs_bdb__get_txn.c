#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_13__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  transaction_t ;
struct TYPE_16__ {int /*<<< orphan*/  db_txn; } ;
typedef  TYPE_1__ trail_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
struct TYPE_17__ {TYPE_3__* fsap_data; } ;
typedef  TYPE_2__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_18__ {TYPE_13__* transactions; } ;
typedef  TYPE_3__ base_fs_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_19__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct TYPE_15__ {int (* get ) (TYPE_13__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_4__ DBT ;

/* Variables and functions */
 int /*<<< orphan*/  BDB_WRAP (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int DB_NOTFOUND ; 
 int /*<<< orphan*/  N_ (char*) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int stub1 (TYPE_13__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_fs_base__err_corrupt_txn (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/ * svn_fs_base__err_no_such_txn (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  svn_fs_base__parse_transaction_skel (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_base__result_dbt (TYPE_4__*) ; 
 int /*<<< orphan*/  svn_fs_base__str_to_dbt (TYPE_4__*,char const*) ; 
 int /*<<< orphan*/  svn_fs_base__track_dbt (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_base__trail_debug (TYPE_1__*,char*,char*) ; 
 int /*<<< orphan*/ * svn_skel__parse (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_bdb__get_txn(transaction_t **txn_p,
                    svn_fs_t *fs,
                    const char *txn_name,
                    trail_t *trail,
                    apr_pool_t *pool)
{
  base_fs_data_t *bfd = fs->fsap_data;
  DBT key, value;
  int db_err;
  svn_skel_t *skel;
  transaction_t *transaction;

  /* Only in the context of this function do we know that the DB call
     will not attempt to modify txn_name, so the cast belongs here.  */
  svn_fs_base__trail_debug(trail, "transactions", "get");
  db_err = bfd->transactions->get(bfd->transactions, trail->db_txn,
                                  svn_fs_base__str_to_dbt(&key, txn_name),
                                  svn_fs_base__result_dbt(&value),
                                  0);
  svn_fs_base__track_dbt(&value, pool);

  if (db_err == DB_NOTFOUND)
    return svn_fs_base__err_no_such_txn(fs, txn_name);
  SVN_ERR(BDB_WRAP(fs, N_("reading transaction"), db_err));

  /* Parse TRANSACTION skel */
  skel = svn_skel__parse(value.data, value.size, pool);
  if (! skel)
    return svn_fs_base__err_corrupt_txn(fs, txn_name);

  /* Convert skel to native type. */
  SVN_ERR(svn_fs_base__parse_transaction_skel(&transaction, skel, pool));
  *txn_p = transaction;
  return SVN_NO_ERROR;
}