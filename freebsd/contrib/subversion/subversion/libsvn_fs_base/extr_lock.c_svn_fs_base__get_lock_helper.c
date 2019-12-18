#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  fs; } ;
typedef  TYPE_1__ trail_t ;
typedef  int /*<<< orphan*/  svn_lock_t ;
struct TYPE_15__ {scalar_t__ apr_err; } ;
typedef  TYPE_2__ svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (TYPE_2__*) ; 
 scalar_t__ SVN_ERR_FS_BAD_LOCK_TOKEN ; 
 scalar_t__ SVN_ERR_FS_LOCK_EXPIRED ; 
 scalar_t__ SVN_ERR_FS_NO_SUCH_LOCK ; 
 TYPE_2__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_2__*) ; 
 TYPE_2__* svn_error_trace (TYPE_2__*) ; 
 TYPE_2__* svn_fs_bdb__lock_get (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_fs_bdb__lock_token_get (char const**,int /*<<< orphan*/ ,char const*,TYPE_1__*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_base__get_lock_helper(svn_lock_t **lock_p,
                             const char *path,
                             trail_t *trail,
                             apr_pool_t *pool)
{
  const char *lock_token;
  svn_error_t *err;

  err = svn_fs_bdb__lock_token_get(&lock_token, trail->fs, path,
                                   trail, pool);

  /* We've deliberately decided that this function doesn't tell the
     caller *why* the lock is unavailable.  */
  if (err && ((err->apr_err == SVN_ERR_FS_NO_SUCH_LOCK)
              || (err->apr_err == SVN_ERR_FS_LOCK_EXPIRED)
              || (err->apr_err == SVN_ERR_FS_BAD_LOCK_TOKEN)))
    {
      svn_error_clear(err);
      *lock_p = NULL;
      return SVN_NO_ERROR;
    }
  else
    SVN_ERR(err);

  /* Same situation here.  */
  err = svn_fs_bdb__lock_get(lock_p, trail->fs, lock_token, trail, pool);
  if (err && ((err->apr_err == SVN_ERR_FS_LOCK_EXPIRED)
              || (err->apr_err == SVN_ERR_FS_BAD_LOCK_TOKEN)))
    {
      svn_error_clear(err);
      *lock_p = NULL;
      return SVN_NO_ERROR;
    }
  else
    SVN_ERR(err);

  return svn_error_trace(err);
}