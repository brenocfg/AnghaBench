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
typedef  struct TYPE_15__   TYPE_11__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  db_txn; } ;
typedef  TYPE_1__ trail_t ;
struct TYPE_17__ {TYPE_3__* fsap_data; } ;
typedef  TYPE_2__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_18__ {TYPE_11__* checksum_reps; } ;
typedef  TYPE_3__ base_fs_data_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_19__ {int /*<<< orphan*/  data; int /*<<< orphan*/  size; } ;
struct TYPE_15__ {int (* get ) (TYPE_11__*,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int (* put ) (TYPE_11__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_4__ DBT ;

/* Variables and functions */
 int /*<<< orphan*/ * BDB_WRAP (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int MAX_KEY_SIZE ; 
 char* NEXT_KEY_KEY ; 
 int /*<<< orphan*/  N_ (char*) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 char* apr_pstrmemdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_11__*,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub2 (TYPE_11__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__next_key (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  svn_fs_base__result_dbt (TYPE_4__*) ; 
 int /*<<< orphan*/  svn_fs_base__str_to_dbt (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  svn_fs_base__track_dbt (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_base__trail_debug (TYPE_1__*,char*,char*) ; 

svn_error_t *svn_fs_bdb__reserve_rep_reuse_id(const char **id_p,
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

  /* Get the current value associated with the `next-key' key in the
     `checksum-reps' table.  */
  svn_fs_base__trail_debug(trail, "checksum-reps", "get");
  SVN_ERR(BDB_WRAP(fs, N_("allocating new representation reuse ID "
                         "(getting 'next-key')"),
                   bfd->checksum_reps->get(bfd->checksum_reps, trail->db_txn,
                                           &query,
                                           svn_fs_base__result_dbt(&result),
                                           0)));
  svn_fs_base__track_dbt(&result, pool);

  /* Set our return value. */
  *id_p = apr_pstrmemdup(pool, result.data, result.size);

  /* Bump to future key. */
  len = result.size;
  svn_fs_base__next_key(result.data, &len, next_key);
  svn_fs_base__trail_debug(trail, "checksum_reps", "put");
  db_err = bfd->checksum_reps->put(bfd->checksum_reps, trail->db_txn,
                                   svn_fs_base__str_to_dbt(&query,
                                                           NEXT_KEY_KEY),
                                   svn_fs_base__str_to_dbt(&result, next_key),
                                   0);

  return BDB_WRAP(fs, N_("bumping next representation reuse ID"), db_err);
}