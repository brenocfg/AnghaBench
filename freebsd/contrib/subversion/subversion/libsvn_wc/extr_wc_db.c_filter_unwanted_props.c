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
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
filter_unwanted_props(apr_hash_t *prop_hash,
                      const char * propname,
                      apr_pool_t *scratch_pool)
{
  apr_hash_index_t *hi;

  for (hi = apr_hash_first(scratch_pool, prop_hash);
       hi;
       hi = apr_hash_next(hi))
    {
      const char *ipropname = apr_hash_this_key(hi);

      if (strcmp(ipropname, propname) != 0)
        svn_hash_sets(prop_hash, ipropname, NULL);
    }
  return;
}