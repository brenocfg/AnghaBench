#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  db_txn; } ;
typedef  TYPE_1__ trail_t ;
struct TYPE_16__ {TYPE_3__* fsap_data; } ;
typedef  TYPE_2__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_17__ {TYPE_10__* strings; } ;
typedef  TYPE_3__ base_fs_data_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_18__ {int /*<<< orphan*/  data; int /*<<< orphan*/  size; } ;
struct TYPE_14__ {int (* cursor ) (TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_4__ DBT ;
typedef  int /*<<< orphan*/  DBC ;

/* Variables and functions */
 int /*<<< orphan*/ * BDB_WRAP (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DB_CURRENT ; 
 int /*<<< orphan*/  DB_SET ; 
 int MAX_KEY_SIZE ; 
 char* NEXT_KEY_KEY ; 
 int /*<<< orphan*/  N_ (char*) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 char* apr_pstrmemdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int svn_bdb_dbc_close (int /*<<< orphan*/ *) ; 
 int svn_bdb_dbc_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int svn_bdb_dbc_put (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__next_key (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  svn_fs_base__result_dbt (TYPE_4__*) ; 
 int /*<<< orphan*/  svn_fs_base__str_to_dbt (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  svn_fs_base__track_dbt (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_base__trail_debug (TYPE_1__*,char*,char*) ; 

__attribute__((used)) static svn_error_t *
get_key_and_bump(svn_fs_t *fs,
                 const char **key,
                 trail_t *trail,
                 apr_pool_t *pool)
{
  base_fs_data_t *bfd = fs->fsap_data;
  DBC *cursor;
  char next_key[MAX_KEY_SIZE];
  apr_size_t key_len;
  int db_err;
  DBT query;
  DBT result;

  /* ### todo: see issue #409 for why bumping the key as part of this
     trail is problematic. */

  /* Open a cursor and move it to the 'next-key' value. We can then fetch
     the contents and use the cursor to overwrite those contents. Since
     this database allows duplicates, we can't do an arbitrary 'put' to
     write the new value -- that would append, not overwrite.  */

  svn_fs_base__trail_debug(trail, "strings", "cursor");
  SVN_ERR(BDB_WRAP(fs, N_("creating cursor for reading a string"),
                   bfd->strings->cursor(bfd->strings, trail->db_txn,
                                        &cursor, 0)));

  /* Advance the cursor to 'next-key' and read it. */

  db_err = svn_bdb_dbc_get(cursor,
                           svn_fs_base__str_to_dbt(&query, NEXT_KEY_KEY),
                           svn_fs_base__result_dbt(&result),
                           DB_SET);
  if (db_err)
    {
      svn_bdb_dbc_close(cursor);
      return BDB_WRAP(fs, N_("getting next-key value"), db_err);
    }

  svn_fs_base__track_dbt(&result, pool);
  *key = apr_pstrmemdup(pool, result.data, result.size);

  /* Bump to future key. */
  key_len = result.size;
  svn_fs_base__next_key(result.data, &key_len, next_key);

  /* Shove the new key back into the database, at the cursor position. */
  db_err = svn_bdb_dbc_put(cursor, &query,
                           svn_fs_base__str_to_dbt(&result, next_key),
                           DB_CURRENT);
  if (db_err)
    {
      svn_bdb_dbc_close(cursor); /* ignore the error, the original is
                                    more important. */
      return BDB_WRAP(fs, N_("bumping next string key"), db_err);
    }

  return BDB_WRAP(fs, N_("closing string-reading cursor"),
                  svn_bdb_dbc_close(cursor));
}