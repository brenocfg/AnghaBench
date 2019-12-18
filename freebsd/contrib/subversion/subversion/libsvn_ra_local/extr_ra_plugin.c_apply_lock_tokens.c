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
typedef  int /*<<< orphan*/  svn_fs_access_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 void* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_val (int /*<<< orphan*/ *) ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_fs_access_add_lock_token2 (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/  svn_fs_get_access (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 char* svn_fspath__join (char const*,void const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
apply_lock_tokens(svn_fs_t *fs,
                  const char *fspath_base,
                  apr_hash_t *lock_tokens,
                  apr_pool_t *access_pool,
                  apr_pool_t *scratch_pool)
{
  if (lock_tokens)
    {
      svn_fs_access_t *access_ctx;

      SVN_ERR(svn_fs_get_access(&access_ctx, fs));

      /* If there is no access context, the filesystem will scream if a
         lock is needed.  */
      if (access_ctx)
        {
          apr_hash_index_t *hi;

          /* Note: we have no use for an iterpool here since the data
             within the loop is copied into ACCESS_POOL.  */

          for (hi = apr_hash_first(scratch_pool, lock_tokens); hi;
               hi = apr_hash_next(hi))
            {
              const void *relpath = apr_hash_this_key(hi);
              const char *token = apr_hash_this_val(hi);
              const char *fspath;

              /* The path needs to live as long as ACCESS_CTX.  */
              fspath = svn_fspath__join(fspath_base, relpath, access_pool);

              /* The token must live as long as ACCESS_CTX.  */
              token = apr_pstrdup(access_pool, token);

              SVN_ERR(svn_fs_access_add_lock_token2(access_ctx, fspath,
                                                    token));
            }
        }
    }

  return SVN_NO_ERROR;
}