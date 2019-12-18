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
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  svn_relpath_basename (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_relpath_dirname (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static apr_hash_t *
get_immediate_children_names(apr_hash_t *paths,
                             const char *parent_rrpath,
                             apr_pool_t *result_pool,
                             apr_pool_t *scratch_pool)
{
  apr_hash_t *children = apr_hash_make(result_pool);
  apr_hash_index_t *hi;

  for (hi = apr_hash_first(scratch_pool, paths); hi; hi = apr_hash_next(hi))
    {
      const char *this_rrpath = apr_hash_this_key(hi);

      if (this_rrpath[0]
          && strcmp(parent_rrpath, svn_relpath_dirname(this_rrpath,
                                                       scratch_pool)) == 0)
        {
          svn_hash_sets(children,
                        svn_relpath_basename(this_rrpath, result_pool), "");
        }
    }

  return children;
}