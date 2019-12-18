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
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  int /*<<< orphan*/  apr_ssize_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_set (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_this_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_this_key_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_this_val (int /*<<< orphan*/ *) ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_string_dup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static apr_hash_t *
string_hash_dup(apr_hash_t *hash, apr_pool_t *pool)
{
  apr_hash_index_t *hi;
  apr_hash_t *new_hash = apr_hash_make(pool);

  for (hi = apr_hash_first(pool, hash); hi; hi = apr_hash_next(hi))
    {
      const char *key = apr_pstrdup(pool, apr_hash_this_key(hi));
      apr_ssize_t klen = apr_hash_this_key_len(hi);
      svn_string_t *val = svn_string_dup(apr_hash_this_val(hi), pool);

      apr_hash_set(new_hash, key, klen, val);
    }
  return new_hash;
}