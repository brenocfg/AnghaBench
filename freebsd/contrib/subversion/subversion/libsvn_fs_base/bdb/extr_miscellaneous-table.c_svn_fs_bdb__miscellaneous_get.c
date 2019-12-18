#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  db_txn; } ;
typedef  TYPE_1__ trail_t ;
struct TYPE_15__ {TYPE_3__* fsap_data; } ;
typedef  TYPE_2__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_16__ {TYPE_11__* miscellaneous; } ;
typedef  TYPE_3__ base_fs_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_17__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct TYPE_13__ {int (* get ) (TYPE_11__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_4__ DBT ;

/* Variables and functions */
 int /*<<< orphan*/  BDB_WRAP (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int DB_NOTFOUND ; 
 int /*<<< orphan*/  N_ (char*) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char* apr_pstrmemdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_11__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__result_dbt (TYPE_4__*) ; 
 int /*<<< orphan*/  svn_fs_base__str_to_dbt (TYPE_4__*,char const*) ; 
 int /*<<< orphan*/  svn_fs_base__track_dbt (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_base__trail_debug (TYPE_1__*,char*,char*) ; 

svn_error_t *
svn_fs_bdb__miscellaneous_get(const char **val,
                              svn_fs_t *fs,
                              const char *key_str,
                              trail_t *trail,
                              apr_pool_t *pool)
{
  base_fs_data_t *bfd = fs->fsap_data;
  DBT key, value;
  int db_err;

  *val = NULL;
  svn_fs_base__trail_debug(trail, "miscellaneous", "get");
  db_err = bfd->miscellaneous->get(bfd->miscellaneous, trail->db_txn,
                                   svn_fs_base__str_to_dbt(&key, key_str),
                                   svn_fs_base__result_dbt(&value), 0);
  svn_fs_base__track_dbt(&value, pool);

  if (db_err != DB_NOTFOUND)
    {
      SVN_ERR(BDB_WRAP(fs, N_("fetching miscellaneous record"), db_err));
      *val = apr_pstrmemdup(pool, value.data, value.size);
    }
  return SVN_NO_ERROR;
}