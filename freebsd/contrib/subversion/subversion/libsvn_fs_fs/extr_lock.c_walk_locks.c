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
typedef  int /*<<< orphan*/  svn_lock_t ;
struct TYPE_4__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ svn_fs_t ;
typedef  int /*<<< orphan*/  (* svn_fs_get_locks_callback_t ) (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  apr_hash_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 char const* digest_path_from_digest (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ lock_expired (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_digest_file (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_single (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
walk_locks(svn_fs_t *fs,
           const char *digest_path,
           svn_fs_get_locks_callback_t get_locks_func,
           void *get_locks_baton,
           svn_boolean_t have_write_lock,
           apr_pool_t *pool)
{
  apr_hash_index_t *hi;
  apr_hash_t *children;
  apr_pool_t *subpool;
  svn_lock_t *lock;

  /* First, send up any locks in the current digest file. */
  SVN_ERR(read_digest_file(&children, &lock, fs->path, digest_path, pool));

  if (lock && lock_expired(lock))
    {
      /* Only remove the lock if we have the write lock.
         Read operations shouldn't change the filesystem. */
      if (have_write_lock)
        SVN_ERR(unlock_single(fs, lock, pool));
    }
  else if (lock)
    {
      SVN_ERR(get_locks_func(get_locks_baton, lock, pool));
    }

  /* Now, report all the child entries (if any; bail otherwise). */
  if (! apr_hash_count(children))
    return SVN_NO_ERROR;
  subpool = svn_pool_create(pool);
  for (hi = apr_hash_first(pool, children); hi; hi = apr_hash_next(hi))
    {
      const char *digest = apr_hash_this_key(hi);
      svn_pool_clear(subpool);

      SVN_ERR(read_digest_file
              (NULL, &lock, fs->path,
               digest_path_from_digest(fs->path, digest, subpool), subpool));

      if (lock && lock_expired(lock))
        {
          /* Only remove the lock if we have the write lock.
             Read operations shouldn't change the filesystem. */
          if (have_write_lock)
            SVN_ERR(unlock_single(fs, lock, pool));
        }
      else if (lock)
        {
          SVN_ERR(get_locks_func(get_locks_baton, lock, pool));
        }
    }
  svn_pool_destroy(subpool);
  return SVN_NO_ERROR;
}