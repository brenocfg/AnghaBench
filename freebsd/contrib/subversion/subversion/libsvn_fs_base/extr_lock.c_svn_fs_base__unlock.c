#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/ * (* svn_fs_lock_callback_t ) (void*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct unlock_args {char const* token; int /*<<< orphan*/  break_lock; int /*<<< orphan*/  path; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs__canonicalize_abspath (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs__check_fs (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_fs_base__retry_txn (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct unlock_args*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txn_body_unlock ; 

svn_error_t *
svn_fs_base__unlock(svn_fs_t *fs,
                    apr_hash_t *targets,
                    svn_boolean_t break_lock,
                    svn_fs_lock_callback_t lock_callback,
                    void *lock_baton,
                    apr_pool_t *result_pool,
                    apr_pool_t *scratch_pool)
{
  apr_hash_index_t *hi;
  svn_error_t *cb_err = SVN_NO_ERROR;
  apr_pool_t *iterpool = svn_pool_create(scratch_pool);

  SVN_ERR(svn_fs__check_fs(fs, TRUE));

  for (hi = apr_hash_first(scratch_pool, targets); hi; hi = apr_hash_next(hi))
    {
      struct unlock_args args;
      const char *path = apr_hash_this_key(hi);
      const char *token = apr_hash_this_val(hi);
      svn_error_t *err;

      svn_pool_clear(iterpool);
      args.path = svn_fs__canonicalize_abspath(path, result_pool);
      args.token = token;
      args.break_lock = break_lock;

      err = svn_fs_base__retry_txn(fs, txn_body_unlock, &args, TRUE,
                                   iterpool);
      if (!cb_err && lock_callback)
        cb_err = lock_callback(lock_baton, path, NULL, err, iterpool);
      svn_error_clear(err);
    }
  svn_pool_destroy(iterpool);

  return svn_error_trace(cb_err);
}