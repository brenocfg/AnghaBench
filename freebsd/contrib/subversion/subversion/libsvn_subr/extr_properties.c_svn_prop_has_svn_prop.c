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
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 scalar_t__ svn_prop_is_svn_prop (char const*) ; 

svn_boolean_t
svn_prop_has_svn_prop(const apr_hash_t *props, apr_pool_t *pool)
{
  apr_hash_index_t *hi;

  if (! props)
    return FALSE;

  for (hi = apr_hash_first(pool, (apr_hash_t *)props); hi;
       hi = apr_hash_next(hi))
    {
      const char *prop_name = apr_hash_this_key(hi);

      if (svn_prop_is_svn_prop(prop_name))
        return TRUE;
    }

  return FALSE;
}