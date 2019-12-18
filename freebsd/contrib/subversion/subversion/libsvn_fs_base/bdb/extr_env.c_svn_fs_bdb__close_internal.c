#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_4__ {scalar_t__ refcount; int /*<<< orphan*/  key; int /*<<< orphan*/  panic; } ;
typedef  TYPE_1__ bdb_env_t ;

/* Variables and functions */
 int /*<<< orphan*/  DB_RUNRECOVERY ; 
 int /*<<< orphan*/  SVN_ERR_FS_BERKELEY_DB ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  apr_hash_set (scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ bdb_cache ; 
 int /*<<< orphan*/ * bdb_close (TYPE_1__*) ; 
 int /*<<< orphan*/  db_strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ svn_atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
svn_fs_bdb__close_internal(bdb_env_t *bdb)
{
  svn_error_t *err = SVN_NO_ERROR;

  if (--bdb->refcount != 0)
    {
      /* If the environment is panicked and automatic recovery is not
         enabled, return an appropriate error. */
#if !SVN_BDB_AUTO_RECOVER
      if (svn_atomic_read(&bdb->panic))
        err = svn_error_create(SVN_ERR_FS_BERKELEY_DB, NULL,
                                db_strerror(DB_RUNRECOVERY));
#endif
    }
  else
    {
      /* If the bdb cache has been set to NULL that means we are
         shutting down, and the pool that holds the bdb cache has
         already been destroyed, so accessing it here would be a Bad
         Thing (tm) */
      if (bdb_cache)
        apr_hash_set(bdb_cache, &bdb->key, sizeof bdb->key, NULL);
      err = bdb_close(bdb);
    }
  return svn_error_trace(err);
}