#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  db_txn; } ;
typedef  TYPE_1__ trail_t ;
struct TYPE_13__ {TYPE_3__* fsap_data; } ;
typedef  TYPE_2__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_14__ {TYPE_7__* strings; } ;
typedef  TYPE_3__ base_fs_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_15__ {int (* cursor ) (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ;int (* put ) (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  DBT ;
typedef  int /*<<< orphan*/  DBC ;

/* Variables and functions */
 int /*<<< orphan*/ * BDB_WRAP (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DB_NEXT_DUP ; 
 int DB_NOTFOUND ; 
 int /*<<< orphan*/  DB_SET ; 
 int /*<<< orphan*/  N_ (char*) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * get_key_and_bump (TYPE_2__*,char const**,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int stub2 (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int svn_bdb_dbc_close (int /*<<< orphan*/ *) ; 
 int svn_bdb_dbc_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__clear_dbt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_base__str_to_dbt (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_fs_base__trail_debug (TYPE_1__*,char*,char*) ; 

svn_error_t *
svn_fs_bdb__string_copy(svn_fs_t *fs,
                        const char **new_key,
                        const char *key,
                        trail_t *trail,
                        apr_pool_t *pool)
{
  base_fs_data_t *bfd = fs->fsap_data;
  DBT query;
  DBT result;
  DBT copykey;
  DBC *cursor;
  int db_err;

  /* Copy off the old key in case the caller is sharing storage
     between the old and new keys. */
  const char *old_key = apr_pstrdup(pool, key);

  SVN_ERR(get_key_and_bump(fs, new_key, trail, pool));

  svn_fs_base__trail_debug(trail, "strings", "cursor");
  SVN_ERR(BDB_WRAP(fs, N_("creating cursor for reading a string"),
                   bfd->strings->cursor(bfd->strings, trail->db_txn,
                                        &cursor, 0)));

  svn_fs_base__str_to_dbt(&query, old_key);
  svn_fs_base__str_to_dbt(&copykey, *new_key);

  svn_fs_base__clear_dbt(&result);

  /* Move to the first record and fetch its data (under BDB's mem mgmt). */
  db_err = svn_bdb_dbc_get(cursor, &query, &result, DB_SET);
  if (db_err)
    {
      svn_bdb_dbc_close(cursor);
      return BDB_WRAP(fs, N_("getting next-key value"), db_err);
    }

  while (1)
    {
      /* ### can we pass a BDB-provided buffer to another BDB function?
         ### they are supposed to have a duration up to certain points
         ### of calling back into BDB, but I'm not sure what the exact
         ### rules are. it is definitely nicer to use BDB buffers here
         ### to simplify things and reduce copies, but... hrm.
      */

      /* Write the data to the database */
      svn_fs_base__trail_debug(trail, "strings", "put");
      db_err = bfd->strings->put(bfd->strings, trail->db_txn,
                                 &copykey, &result, 0);
      if (db_err)
        {
          svn_bdb_dbc_close(cursor);
          return BDB_WRAP(fs, N_("writing copied data"), db_err);
        }

      /* Read the next chunk. Terminate loop if we're done. */
      svn_fs_base__clear_dbt(&result);
      db_err = svn_bdb_dbc_get(cursor, &query, &result, DB_NEXT_DUP);
      if (db_err == DB_NOTFOUND)
        break;
      if (db_err)
        {
          svn_bdb_dbc_close(cursor);
          return BDB_WRAP(fs, N_("fetching string data for a copy"), db_err);
        }
    }

  return BDB_WRAP(fs, N_("closing string-reading cursor"),
                  svn_bdb_dbc_close(cursor));
}