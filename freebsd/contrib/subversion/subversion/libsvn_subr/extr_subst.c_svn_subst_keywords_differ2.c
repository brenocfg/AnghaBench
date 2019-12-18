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
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_ssize_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 unsigned int apr_hash_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_get (int /*<<< orphan*/ *,void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_this (int /*<<< orphan*/ *,void const**,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  svn_string_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_boolean_t
svn_subst_keywords_differ2(apr_hash_t *a,
                           apr_hash_t *b,
                           svn_boolean_t compare_values,
                           apr_pool_t *pool)
{
  apr_hash_index_t *hi;
  unsigned int a_count, b_count;

  /* An empty hash is logically equal to a NULL,
   * as far as this API is concerned. */
  a_count = (a == NULL) ? 0 : apr_hash_count(a);
  b_count = (b == NULL) ? 0 : apr_hash_count(b);

  if (a_count != b_count)
    return TRUE;

  if (a_count == 0)
    return FALSE;

  /* The hashes are both non-NULL, and have the same number of items.
   * We must check that every item of A is present in B. */
  for (hi = apr_hash_first(pool, a); hi; hi = apr_hash_next(hi))
    {
      const void *key;
      apr_ssize_t klen;
      void *void_a_val;
      svn_string_t *a_val, *b_val;

      apr_hash_this(hi, &key, &klen, &void_a_val);
      a_val = void_a_val;
      b_val = apr_hash_get(b, key, klen);

      if (!b_val || (compare_values && !svn_string_compare(a_val, b_val)))
        return TRUE;
    }

  return FALSE;
}