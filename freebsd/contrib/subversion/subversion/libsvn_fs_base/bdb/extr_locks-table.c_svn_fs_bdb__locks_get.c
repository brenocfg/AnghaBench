#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_37__   TYPE_6__ ;
typedef  struct TYPE_36__   TYPE_5__ ;
typedef  struct TYPE_35__   TYPE_3__ ;
typedef  struct TYPE_34__   TYPE_2__ ;
typedef  struct TYPE_33__   TYPE_24__ ;
typedef  struct TYPE_32__   TYPE_1__ ;

/* Type definitions */
struct TYPE_32__ {int /*<<< orphan*/  db_txn; } ;
typedef  TYPE_1__ trail_t ;
typedef  int /*<<< orphan*/  svn_lock_t ;
struct TYPE_34__ {TYPE_5__* fsap_data; } ;
typedef  TYPE_2__ svn_fs_t ;
typedef  TYPE_3__* (* svn_fs_get_locks_callback_t ) (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;
struct TYPE_35__ {scalar_t__ apr_err; } ;
typedef  TYPE_3__ svn_error_t ;
typedef  scalar_t__ svn_depth_t ;
struct TYPE_36__ {TYPE_24__* lock_tokens; } ;
typedef  TYPE_5__ base_fs_data_t ;
typedef  scalar_t__ apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_37__ {scalar_t__ size; int /*<<< orphan*/  data; int /*<<< orphan*/  flags; } ;
struct TYPE_33__ {int (* cursor ) (TYPE_24__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_6__ DBT ;
typedef  int /*<<< orphan*/  DBC ;

/* Variables and functions */
 TYPE_3__* BDB_WRAP (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DB_DBT_MALLOC ; 
 int /*<<< orphan*/  DB_NEXT ; 
 int DB_NOTFOUND ; 
 int /*<<< orphan*/  DB_SET_RANGE ; 
 int /*<<< orphan*/  N_ (char*) ; 
 int /*<<< orphan*/  SVN_ERR (TYPE_3__*) ; 
 scalar_t__ SVN_ERR_FS_BAD_LOCK_TOKEN ; 
 scalar_t__ SVN_ERR_FS_LOCK_EXPIRED ; 
 scalar_t__ SVN_ERR_FS_NO_SUCH_LOCK ; 
 TYPE_3__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_VA_NULL ; 
 char* apr_pstrcat (int /*<<< orphan*/ *,char const*,char*,int /*<<< orphan*/ ) ; 
 char* apr_pstrmemdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_3__* get_lock (int /*<<< orphan*/ **,TYPE_2__*,char const*,char const*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,scalar_t__) ; 
 int stub1 (TYPE_24__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int svn_bdb_dbc_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_bdb_dbc_get (int /*<<< orphan*/ *,TYPE_6__*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 scalar_t__ svn_depth_empty ; 
 scalar_t__ svn_depth_files ; 
 scalar_t__ svn_depth_immediates ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_3__*) ; 
 TYPE_3__* svn_error_trace (TYPE_3__*) ; 
 TYPE_6__* svn_fs_base__result_dbt (TYPE_6__*) ; 
 int /*<<< orphan*/  svn_fs_base__str_to_dbt (TYPE_6__*,char const*) ; 
 int /*<<< orphan*/  svn_fs_base__track_dbt (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_base__trail_debug (TYPE_1__*,char*,char*) ; 
 TYPE_3__* svn_fs_bdb__lock_token_get (char const**,TYPE_2__*,char const*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fspath__is_root (char const*,scalar_t__) ; 
 char* svn_fspath__skip_ancestor (char const*,char const*) ; 
 int svn_path_component_count (char const*) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_bdb__locks_get(svn_fs_t *fs,
                      const char *path,
                      svn_depth_t depth,
                      svn_fs_get_locks_callback_t get_locks_func,
                      void *get_locks_baton,
                      trail_t *trail,
                      apr_pool_t *pool)
{
  base_fs_data_t *bfd = fs->fsap_data;
  DBC *cursor;
  DBT key, value;
  int db_err, db_c_err;
  apr_pool_t *subpool = svn_pool_create(pool);
  const char *lock_token;
  svn_lock_t *lock;
  svn_error_t *err;
  const char *lookup_path = path;
  apr_size_t lookup_len;

  /* First, try to lookup PATH itself. */
  err = svn_fs_bdb__lock_token_get(&lock_token, fs, path, trail, pool);
  if (err && ((err->apr_err == SVN_ERR_FS_LOCK_EXPIRED)
              || (err->apr_err == SVN_ERR_FS_BAD_LOCK_TOKEN)
              || (err->apr_err == SVN_ERR_FS_NO_SUCH_LOCK)))
    {
      svn_error_clear(err);
    }
  else if (err)
    {
      return svn_error_trace(err);
    }
  else
    {
      SVN_ERR(get_lock(&lock, fs, path, lock_token, trail, pool));
      if (lock && get_locks_func)
        {
          SVN_ERR(get_locks_func(get_locks_baton, lock, pool));

          /* Found a lock so PATH is a file and we can ignore depth */
          return SVN_NO_ERROR;
        }
    }

  /* If we're only looking at PATH itself (depth = empty), stop here. */
  if (depth == svn_depth_empty)
    return SVN_NO_ERROR;

  /* Now go hunt for possible children of PATH. */

  svn_fs_base__trail_debug(trail, "lock-tokens", "cursor");
  db_err = bfd->lock_tokens->cursor(bfd->lock_tokens, trail->db_txn,
                                    &cursor, 0);
  SVN_ERR(BDB_WRAP(fs, N_("creating cursor for reading lock tokens"),
                   db_err));

  /* Since the key is going to be returned as well as the value make
     sure BDB malloc's the returned key.  */
  svn_fs_base__str_to_dbt(&key, lookup_path);
  key.flags |= DB_DBT_MALLOC;

  /* Get the first matching key that is either equal or greater than
     the one passed in, by passing in the DB_RANGE_SET flag.  */
  db_err = svn_bdb_dbc_get(cursor, &key, svn_fs_base__result_dbt(&value),
                           DB_SET_RANGE);

  if (!svn_fspath__is_root(path, strlen(path)))
    lookup_path = apr_pstrcat(pool, path, "/", SVN_VA_NULL);
  lookup_len = strlen(lookup_path);

  /* As long as the prefix of the returned KEY matches LOOKUP_PATH we
     know it is either LOOKUP_PATH or a decendant thereof.  */
  while ((! db_err)
         && lookup_len < key.size
         && strncmp(lookup_path, key.data, lookup_len) == 0)
    {
      const char *child_path;

      svn_pool_clear(subpool);

      svn_fs_base__track_dbt(&key, subpool);
      svn_fs_base__track_dbt(&value, subpool);

      /* Create a usable path and token in temporary memory. */
      child_path = apr_pstrmemdup(subpool, key.data, key.size);
      lock_token = apr_pstrmemdup(subpool, value.data, value.size);

      if ((depth == svn_depth_files) || (depth == svn_depth_immediates))
        {
          /* On the assumption that we only store locks for files,
             depth=files and depth=immediates should boil down to the
             same set of results.  So just see if CHILD_PATH is an
             immediate child of PATH.  If not, we don't care about
             this item.   */
          const char *rel_path = svn_fspath__skip_ancestor(path, child_path);
          if (!rel_path || (svn_path_component_count(rel_path) != 1))
            goto loop_it;
        }

      /* Get the lock for CHILD_PATH.  */
      err = get_lock(&lock, fs, child_path, lock_token, trail, subpool);
      if (err)
        {
          svn_bdb_dbc_close(cursor);
          return svn_error_trace(err);
        }

      /* Lock is verified, hand it off to our callback. */
      if (lock && get_locks_func)
        {
          err = get_locks_func(get_locks_baton, lock, subpool);
          if (err)
            {
              svn_bdb_dbc_close(cursor);
              return svn_error_trace(err);
            }
        }

    loop_it:
      svn_fs_base__result_dbt(&key);
      svn_fs_base__result_dbt(&value);
      db_err = svn_bdb_dbc_get(cursor, &key, &value, DB_NEXT);
    }

  svn_pool_destroy(subpool);
  db_c_err = svn_bdb_dbc_close(cursor);

  if (db_err && (db_err != DB_NOTFOUND))
    SVN_ERR(BDB_WRAP(fs, N_("fetching lock tokens"), db_err));
  if (db_c_err)
    SVN_ERR(BDB_WRAP(fs, N_("fetching lock tokens (closing cursor)"),
                     db_c_err));

  return SVN_NO_ERROR;
}