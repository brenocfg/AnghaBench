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
typedef  int svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_ssize_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 scalar_t__ apr_hash_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_get (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_this (int /*<<< orphan*/ *,void const**,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  svn_string_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_boolean_t
svn_fs__prop_lists_equal(apr_hash_t *a,
                         apr_hash_t *b,
                         apr_pool_t *pool)
{
  apr_hash_index_t *hi;

  /* Quick checks and special cases. */
  if (a == b)
    return TRUE;

  if (a == NULL)
    return apr_hash_count(b) == 0;
  if (b == NULL)
    return apr_hash_count(a) == 0;

  if (apr_hash_count(a) != apr_hash_count(b))
    return FALSE;

  /* Compare prop by prop. */
  for (hi = apr_hash_first(pool, a); hi; hi = apr_hash_next(hi))
    {
      const char *key;
      apr_ssize_t klen;
      svn_string_t *val_a, *val_b;

      apr_hash_this(hi, (const void **)&key, &klen, (void **)&val_a);
      val_b = apr_hash_get(b, key, klen);

      if (!val_b || !svn_string_compare(val_a, val_b))
        return FALSE;
    }

  /* No difference found. */
  return TRUE;
}