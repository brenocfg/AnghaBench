#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_ra_session_t ;
struct TYPE_3__ {int /*<<< orphan*/  token; } ;
typedef  TYPE_1__ svn_lock_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_CLIENT_MISSING_LOCK_TOKEN ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_get_lock (int /*<<< orphan*/ *,TYPE_1__**,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
fetch_tokens(svn_ra_session_t *ra_session, apr_hash_t *path_tokens,
             apr_pool_t *pool)
{
  apr_hash_index_t *hi;
  apr_pool_t *iterpool = svn_pool_create(pool);

  for (hi = apr_hash_first(pool, path_tokens); hi; hi = apr_hash_next(hi))
    {
      const char *path = apr_hash_this_key(hi);
      svn_lock_t *lock;

      svn_pool_clear(iterpool);

      SVN_ERR(svn_ra_get_lock(ra_session, &lock, path, iterpool));

      if (! lock)
        return svn_error_createf
          (SVN_ERR_CLIENT_MISSING_LOCK_TOKEN, NULL,
           _("'%s' is not locked"), path);

      svn_hash_sets(path_tokens, path, apr_pstrdup(pool, lock->token));
    }

  svn_pool_destroy(iterpool);
  return SVN_NO_ERROR;
}