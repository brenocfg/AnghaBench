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
typedef  int /*<<< orphan*/  (* filter_func_t ) (char const*) ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 void* apr_hash_this_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,char const*,void*) ; 

__attribute__((used)) static apr_hash_t *
filter_props(int *filtered_count, apr_hash_t *props,
             filter_func_t filter,
             apr_pool_t *pool)
{
  apr_hash_index_t *hi;
  apr_hash_t *filtered = apr_hash_make(pool);
  *filtered_count = 0;

  for (hi = apr_hash_first(pool, props); hi ; hi = apr_hash_next(hi))
    {
      const char *propname = apr_hash_this_key(hi);
      void *propval = apr_hash_this_val(hi);

      /* Copy all properties:
          - not matching the exclude pattern if provided OR
          - matching the include pattern if provided */
      if (!filter || !filter(propname))
        {
          svn_hash_sets(filtered, propname, propval);
        }
      else
        {
          *filtered_count += 1;
        }
    }

  return filtered;
}