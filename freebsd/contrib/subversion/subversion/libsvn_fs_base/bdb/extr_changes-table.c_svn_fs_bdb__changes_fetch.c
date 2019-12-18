#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_15__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  db_txn; } ;
typedef  TYPE_1__ trail_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
struct TYPE_20__ {TYPE_4__* fsap_data; } ;
typedef  TYPE_2__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_21__ {scalar_t__ kind; int /*<<< orphan*/  path; } ;
typedef  TYPE_3__ change_t ;
struct TYPE_22__ {TYPE_15__* changes; } ;
typedef  TYPE_4__ base_fs_data_t ;
typedef  int /*<<< orphan*/  apr_ssize_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;
struct TYPE_23__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct TYPE_18__ {int (* cursor ) (TYPE_15__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_5__ DBT ;
typedef  int /*<<< orphan*/  DBC ;

/* Variables and functions */
 int /*<<< orphan*/ * BDB_WRAP (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DB_NEXT_DUP ; 
 int DB_NOTFOUND ; 
 int /*<<< orphan*/  DB_SET ; 
 int /*<<< orphan*/  N_ (char*) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SVN_ERR_FS_CORRUPT ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_set (int /*<<< orphan*/ *,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_this (int /*<<< orphan*/ *,void const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fold_change (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int stub1 (TYPE_15__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int svn_bdb_dbc_close (int /*<<< orphan*/ *) ; 
 int svn_bdb_dbc_get (int /*<<< orphan*/ *,TYPE_5__*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_base__parse_change_skel (TYPE_3__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_base__result_dbt (TYPE_5__*) ; 
 int /*<<< orphan*/  svn_fs_base__str_to_dbt (TYPE_5__*,char const*) ; 
 int /*<<< orphan*/  svn_fs_base__track_dbt (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_base__trail_debug (TYPE_1__*,char*,char*) ; 
 scalar_t__ svn_fs_path_change_delete ; 
 scalar_t__ svn_fs_path_change_replace ; 
 char* svn_fspath__skip_ancestor (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_skel__parse (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_bdb__changes_fetch(apr_hash_t **changes_p,
                          svn_fs_t *fs,
                          const char *key,
                          trail_t *trail,
                          apr_pool_t *pool)
{
  base_fs_data_t *bfd = fs->fsap_data;
  DBC *cursor;
  DBT query, result;
  int db_err = 0, db_c_err = 0;
  svn_error_t *err = SVN_NO_ERROR;
  apr_hash_t *changes = apr_hash_make(pool);
  apr_pool_t *subpool = svn_pool_create(pool);
  apr_pool_t *iterpool = svn_pool_create(pool);
  apr_hash_t *deletions = apr_hash_make(subpool);

  /* Get a cursor on the first record matching KEY, and then loop over
     the records, adding them to the return array. */
  svn_fs_base__trail_debug(trail, "changes", "cursor");
  SVN_ERR(BDB_WRAP(fs, N_("creating cursor for reading changes"),
                   bfd->changes->cursor(bfd->changes, trail->db_txn,
                                        &cursor, 0)));

  /* Advance the cursor to the key that we're looking for. */
  svn_fs_base__str_to_dbt(&query, key);
  svn_fs_base__result_dbt(&result);
  db_err = svn_bdb_dbc_get(cursor, &query, &result, DB_SET);
  if (! db_err)
    svn_fs_base__track_dbt(&result, pool);

  while (! db_err)
    {
      change_t *change;
      svn_skel_t *result_skel;

      /* Clear the per-iteration subpool. */
      svn_pool_clear(iterpool);

      /* RESULT now contains a change record associated with KEY.  We
         need to parse that skel into an change_t structure ...  */
      result_skel = svn_skel__parse(result.data, result.size, iterpool);
      if (! result_skel)
        {
          err = svn_error_createf(SVN_ERR_FS_CORRUPT, NULL,
                                  _("Error reading changes for key '%s'"),
                                  key);
          goto cleanup;
        }
      err = svn_fs_base__parse_change_skel(&change, result_skel, iterpool);
      if (err)
        goto cleanup;

      /* ... and merge it with our return hash.  */
      err = fold_change(changes, deletions, change);
      if (err)
        goto cleanup;

      /* Now, if our change was a deletion or replacement, we have to
         blow away any changes thus far on paths that are (or, were)
         children of this path.
         ### i won't bother with another iteration pool here -- at
             most we talking about a few extra dups of paths into what
             is already a temporary subpool.
      */
      if ((change->kind == svn_fs_path_change_delete)
          || (change->kind == svn_fs_path_change_replace))
        {
          apr_hash_index_t *hi;

          for (hi = apr_hash_first(iterpool, changes);
               hi;
               hi = apr_hash_next(hi))
            {
              /* KEY is the path. */
              const void *hashkey;
              apr_ssize_t klen;
              const char *child_relpath;

              apr_hash_this(hi, &hashkey, &klen, NULL);

              /* If we come across our own path, ignore it.
                 If we come across a child of our path, remove it. */
              child_relpath = svn_fspath__skip_ancestor(change->path, hashkey);
              if (child_relpath && *child_relpath)
                apr_hash_set(changes, hashkey, klen, NULL);
            }
        }

      /* Advance the cursor to the next record with this same KEY, and
         fetch that record. */
      svn_fs_base__result_dbt(&result);
      db_err = svn_bdb_dbc_get(cursor, &query, &result, DB_NEXT_DUP);
      if (! db_err)
        svn_fs_base__track_dbt(&result, pool);
    }

  /* Destroy the per-iteration subpool. */
  svn_pool_destroy(iterpool);
  svn_pool_destroy(subpool);

  /* If there are no (more) change records for this KEY, we're
     finished.  Just return the (possibly empty) array.  Any other
     error, however, needs to get handled appropriately.  */
  if (db_err && (db_err != DB_NOTFOUND))
    err = BDB_WRAP(fs, N_("fetching changes"), db_err);

 cleanup:
  /* Close the cursor. */
  db_c_err = svn_bdb_dbc_close(cursor);

  /* If we had an error prior to closing the cursor, return the error. */
  if (err)
    return svn_error_trace(err);

  /* If our only error thus far was when we closed the cursor, return
     that error. */
  if (db_c_err)
    SVN_ERR(BDB_WRAP(fs, N_("closing changes cursor"), db_c_err));

  /* Finally, set our return variable and get outta here. */
  *changes_p = changes;
  return SVN_NO_ERROR;
}