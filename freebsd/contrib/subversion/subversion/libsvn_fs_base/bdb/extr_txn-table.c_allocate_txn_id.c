#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  db_txn; } ;
typedef  TYPE_1__ trail_t ;
struct TYPE_18__ {TYPE_3__* fsap_data; } ;
typedef  TYPE_2__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_19__ {TYPE_9__* transactions; } ;
typedef  TYPE_3__ base_fs_data_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_21__ {int (* get ) (TYPE_9__*,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int (* put ) (TYPE_9__*,int /*<<< orphan*/ ,TYPE_4__*,TYPE_4__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_20__ {int /*<<< orphan*/  data; int /*<<< orphan*/  size; } ;
typedef  TYPE_4__ DBT ;

/* Variables and functions */
 int /*<<< orphan*/ * BDB_WRAP (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int MAX_KEY_SIZE ; 
 char* NEXT_KEY_KEY ; 
 int /*<<< orphan*/  N_ (char*) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 char* apr_pstrmemdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_9__*,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub2 (TYPE_9__*,int /*<<< orphan*/ ,TYPE_4__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__next_key (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  svn_fs_base__result_dbt (TYPE_4__*) ; 
 int /*<<< orphan*/  svn_fs_base__str_to_dbt (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  svn_fs_base__track_dbt (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_base__trail_debug (TYPE_1__*,char*,char*) ; 

__attribute__((used)) static svn_error_t *
allocate_txn_id(const char **id_p,
                svn_fs_t *fs,
                trail_t *trail,
                apr_pool_t *pool)
{
  base_fs_data_t *bfd = fs->fsap_data;
  DBT query, result;
  apr_size_t len;
  char next_key[MAX_KEY_SIZE];
  int db_err;

  svn_fs_base__str_to_dbt(&query, NEXT_KEY_KEY);

  /* Get the current value associated with the `next-key' key in the table.  */
  svn_fs_base__trail_debug(trail, "transactions", "get");
  SVN_ERR(BDB_WRAP(fs, N_("allocating new transaction ID (getting 'next-key')"),
                   bfd->transactions->get(bfd->transactions, trail->db_txn,
                                          &query,
                                          svn_fs_base__result_dbt(&result),
                                          0)));
  svn_fs_base__track_dbt(&result, pool);

  /* Set our return value. */
  *id_p = apr_pstrmemdup(pool, result.data, result.size);

  /* Bump to future key. */
  len = result.size;
  svn_fs_base__next_key(result.data, &len, next_key);
  svn_fs_base__str_to_dbt(&query, NEXT_KEY_KEY);
  svn_fs_base__str_to_dbt(&result, next_key);
  svn_fs_base__trail_debug(trail, "transactions", "put");
  db_err = bfd->transactions->put(bfd->transactions, trail->db_txn,
                                  &query, &result, 0);

  return BDB_WRAP(fs, N_("bumping next transaction key"), db_err);
}