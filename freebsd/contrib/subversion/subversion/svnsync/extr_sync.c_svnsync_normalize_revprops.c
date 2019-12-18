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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_this_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  normalize_string (int /*<<< orphan*/  const**,scalar_t__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*) ; 
 scalar_t__ svn_prop_needs_translation (char const*) ; 

svn_error_t *
svnsync_normalize_revprops(apr_hash_t *rev_props,
                           int *normalized_count,
                           const char *source_prop_encoding,
                           apr_pool_t *pool)
{
  apr_hash_index_t *hi;
  *normalized_count = 0;

  for (hi = apr_hash_first(pool, rev_props);
       hi;
       hi = apr_hash_next(hi))
    {
      const char *propname = apr_hash_this_key(hi);
      const svn_string_t *propval = apr_hash_this_val(hi);

      if (svn_prop_needs_translation(propname))
        {
          svn_boolean_t was_normalized;
          SVN_ERR(normalize_string(&propval, &was_normalized,
                  source_prop_encoding, pool, pool));

          /* Replace the existing prop value. */
          svn_hash_sets(rev_props, propname, propval);

          if (was_normalized)
            (*normalized_count)++; /* Count it. */
        }
    }
  return SVN_NO_ERROR;
}