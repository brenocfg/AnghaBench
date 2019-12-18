#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_6__ {scalar_t__ env; int /*<<< orphan*/  error_info; scalar_t__ pool; } ;
typedef  TYPE_1__ bdb_env_t ;
struct TYPE_7__ {scalar_t__ env; TYPE_5__* error_info; TYPE_1__* bdb; } ;
typedef  TYPE_2__ bdb_env_baton_t ;
struct TYPE_8__ {scalar_t__ refcount; int /*<<< orphan*/  pending_errors; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/  SVN_MUTEX__WITH_LOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  apr_threadkey_private_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bdb_cache_lock ; 
 int /*<<< orphan*/  free (TYPE_5__*) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_bdb__close_internal (TYPE_1__*) ; 

svn_error_t *
svn_fs_bdb__close(bdb_env_baton_t *bdb_baton)
{
  bdb_env_t *bdb = bdb_baton->bdb;

  SVN_ERR_ASSERT(bdb_baton->env == bdb_baton->bdb->env);
  SVN_ERR_ASSERT(bdb_baton->error_info->refcount > 0);

  /* Neutralize bdb_baton's pool cleanup to prevent double-close. See
     cleanup_env_baton(). */
  bdb_baton->bdb = NULL;

  /* Note that we only bother with this cleanup if the pool is non-NULL, to
     guard against potential races between this and the cleanup_env cleanup
     callback.  It's not clear if that can actually happen, but better safe
     than sorry. */
  if (0 == --bdb_baton->error_info->refcount && bdb->pool)
    {
      svn_error_clear(bdb_baton->error_info->pending_errors);
#if APR_HAS_THREADS
      free(bdb_baton->error_info);
      apr_threadkey_private_set(NULL, bdb->error_info);
#endif
    }

  /* This may run during final pool cleanup when the lock is NULL. */
  SVN_MUTEX__WITH_LOCK(bdb_cache_lock, svn_fs_bdb__close_internal(bdb));

  return SVN_NO_ERROR;
}