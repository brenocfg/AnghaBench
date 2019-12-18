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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,char const*,char const*) ; 
 char* svn_uri_skip_ancestor (char const*,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
collect_lock_tokens(apr_hash_t **result,
                    apr_hash_t *all_tokens,
                    const char *base_url,
                    apr_pool_t *pool)
{
  apr_hash_index_t *hi;

  *result = apr_hash_make(pool);

  for (hi = apr_hash_first(pool, all_tokens); hi; hi = apr_hash_next(hi))
    {
      const char *url = apr_hash_this_key(hi);
      const char *token = apr_hash_this_val(hi);
      const char *relpath = svn_uri_skip_ancestor(base_url, url, pool);

      if (relpath)
        {
          svn_hash_sets(*result, relpath, token);
        }
    }

  return SVN_NO_ERROR;
}