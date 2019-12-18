#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  trail_t ;
typedef  int /*<<< orphan*/  svn_lock_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
struct TYPE_9__ {scalar_t__ apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ SVN_ERR_FS_BAD_LOCK_TOKEN ; 
 scalar_t__ SVN_ERR_FS_LOCK_EXPIRED ; 
 TYPE_1__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 TYPE_1__* svn_error_trace (TYPE_1__*) ; 
 TYPE_1__* svn_fs_bdb__lock_get (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_fs_bdb__lock_token_delete (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_lock(svn_lock_t **lock_p,
         svn_fs_t *fs,
         const char *path,
         const char *lock_token,
         trail_t *trail,
         apr_pool_t *pool)
{
  svn_error_t *err = SVN_NO_ERROR;
  *lock_p = NULL;

  /* Make sure the token points to an existing, non-expired lock, by
     doing a lookup in the `locks' table.  Use 'pool'. */
  err = svn_fs_bdb__lock_get(lock_p, fs, lock_token, trail, pool);
  if (err && ((err->apr_err == SVN_ERR_FS_LOCK_EXPIRED)
              || (err->apr_err == SVN_ERR_FS_BAD_LOCK_TOKEN)))
    {
      svn_error_clear(err);

      /* If `locks' doesn't have the lock, then we should lose it
         from `lock-tokens' table as well, then skip to the next
         matching path-key. */
      err = svn_fs_bdb__lock_token_delete(fs, path, trail, pool);
    }
  return svn_error_trace(err);
}