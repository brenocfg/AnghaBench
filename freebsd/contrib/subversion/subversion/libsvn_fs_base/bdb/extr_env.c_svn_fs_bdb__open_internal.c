#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_13__ {int flags; int refcount; int /*<<< orphan*/  env; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ bdb_env_t ;
typedef  int /*<<< orphan*/  bdb_env_key_t ;
struct TYPE_14__ {TYPE_4__* error_info; TYPE_1__* bdb; int /*<<< orphan*/  env; } ;
typedef  TYPE_2__ bdb_env_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_15__ {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int DB_PRIVATE ; 
 int /*<<< orphan*/  DB_RUNRECOVERY ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_BERKELEY_DB ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  apr_hash_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 TYPE_2__* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  apr_pool_cleanup_null ; 
 int /*<<< orphan*/  apr_pool_cleanup_register (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bdb_cache ; 
 TYPE_1__* bdb_cache_get (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  bdb_cache_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bdb_cache_pool ; 
 int /*<<< orphan*/  bdb_close (TYPE_1__*) ; 
 int /*<<< orphan*/ * bdb_open (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  cleanup_env_baton ; 
 int /*<<< orphan*/  create_env (TYPE_1__**,char const*,int /*<<< orphan*/ ) ; 
 char* db_strerror (int /*<<< orphan*/ ) ; 
 TYPE_4__* get_error_info (TYPE_1__*) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_create (int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
svn_fs_bdb__open_internal(bdb_env_baton_t **bdb_batonp,
                          const char *path,
                          u_int32_t flags, int mode,
                          apr_pool_t *pool)
{
  bdb_env_key_t key;
  bdb_env_t *bdb;
  svn_boolean_t panic;

  /* We can safely discard the open DB_CONFIG file handle.  If the
     environment descriptor is in the cache, the key's immutability is
     guaranteed.  If it's not, we don't care if the key changes,
     between here and the actual insertion of the newly-created
     environment into the cache, because no other thread can touch the
     cache in the meantime. */
  SVN_ERR(bdb_cache_key(&key, NULL, path, pool));

  bdb = bdb_cache_get(&key, &panic);
  if (panic)
    return svn_error_create(SVN_ERR_FS_BERKELEY_DB, NULL,
                            db_strerror(DB_RUNRECOVERY));

  /* Make sure that the environment's open flags haven't changed. */
  if (bdb && bdb->flags != flags)
    {
      /* Handle changes to the DB_PRIVATE flag specially */
      if ((flags ^ bdb->flags) & DB_PRIVATE)
        {
          if (flags & DB_PRIVATE)
            return svn_error_create(SVN_ERR_FS_BERKELEY_DB, NULL,
                                    "Reopening a public Berkeley DB"
                                    " environment with private attributes");
          else
            return svn_error_create(SVN_ERR_FS_BERKELEY_DB, NULL,
                                    "Reopening a private Berkeley DB"
                                    " environment with public attributes");
        }

      /* Otherwise return a generic "flags-mismatch" error. */
      return svn_error_create(SVN_ERR_FS_BERKELEY_DB, NULL,
                              "Reopening a Berkeley DB environment"
                              " with different attributes");
    }

  if (!bdb)
    {
      svn_error_t *err;

      SVN_ERR(create_env(&bdb, path, svn_pool_create(bdb_cache_pool)));
      err = bdb_open(bdb, flags, mode);
      if (err)
        {
          /* Clean up, and we can't do anything about returned errors. */
          svn_error_clear(bdb_close(bdb));
          return svn_error_trace(err);
        }

      apr_hash_set(bdb_cache, &bdb->key, sizeof bdb->key, bdb);
      bdb->flags = flags;
      bdb->refcount = 1;
    }
  else
    {
      ++bdb->refcount;
    }

  *bdb_batonp = apr_palloc(pool, sizeof **bdb_batonp);
  (*bdb_batonp)->env = bdb->env;
  (*bdb_batonp)->bdb = bdb;
  (*bdb_batonp)->error_info = get_error_info(bdb);
  ++(*bdb_batonp)->error_info->refcount;
  apr_pool_cleanup_register(pool, *bdb_batonp, cleanup_env_baton,
                            apr_pool_cleanup_null);

  return SVN_NO_ERROR;
}