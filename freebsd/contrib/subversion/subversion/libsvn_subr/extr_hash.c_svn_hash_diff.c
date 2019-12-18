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
typedef  int /*<<< orphan*/  (* svn_hash_diff_func_t ) (void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_ssize_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ apr_hash_get (int /*<<< orphan*/ *,void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_this (int /*<<< orphan*/ *,void const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  stub2 (void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  stub3 (void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  svn_hash_diff_key_a ; 
 int /*<<< orphan*/  svn_hash_diff_key_b ; 
 int /*<<< orphan*/  svn_hash_diff_key_both ; 

svn_error_t *
svn_hash_diff(apr_hash_t *hash_a,
              apr_hash_t *hash_b,
              svn_hash_diff_func_t diff_func,
              void *diff_func_baton,
              apr_pool_t *pool)
{
  apr_hash_index_t *hi;

  if (hash_a)
    for (hi = apr_hash_first(pool, hash_a); hi; hi = apr_hash_next(hi))
      {
        const void *key;
        apr_ssize_t klen;

        apr_hash_this(hi, &key, &klen, NULL);

        if (hash_b && (apr_hash_get(hash_b, key, klen)))
          SVN_ERR((*diff_func)(key, klen, svn_hash_diff_key_both,
                               diff_func_baton));
        else
          SVN_ERR((*diff_func)(key, klen, svn_hash_diff_key_a,
                               diff_func_baton));
      }

  if (hash_b)
    for (hi = apr_hash_first(pool, hash_b); hi; hi = apr_hash_next(hi))
      {
        const void *key;
        apr_ssize_t klen;

        apr_hash_this(hi, &key, &klen, NULL);

        if (! (hash_a && apr_hash_get(hash_a, key, klen)))
          SVN_ERR((*diff_func)(key, klen, svn_hash_diff_key_b,
                               diff_func_baton));
      }

  return SVN_NO_ERROR;
}