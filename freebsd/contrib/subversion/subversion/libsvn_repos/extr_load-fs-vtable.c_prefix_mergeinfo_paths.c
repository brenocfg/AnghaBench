#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_rangelist_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_this_val (int /*<<< orphan*/ *) ; 
 char* svn_fspath__canonicalize (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_mergeinfo_parse (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_mergeinfo_to_string (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* svn_relpath_canonicalize (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_relpath_join (char const*,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
prefix_mergeinfo_paths(svn_string_t **mergeinfo_val,
                       const svn_string_t *mergeinfo_orig,
                       const char *parent_dir,
                       apr_pool_t *pool)
{
  apr_hash_t *prefixed_mergeinfo, *mergeinfo;
  apr_hash_index_t *hi;

  SVN_ERR(svn_mergeinfo_parse(&mergeinfo, mergeinfo_orig->data, pool));
  prefixed_mergeinfo = apr_hash_make(pool);
  for (hi = apr_hash_first(pool, mergeinfo); hi; hi = apr_hash_next(hi))
    {
      const char *merge_source = apr_hash_this_key(hi);
      svn_rangelist_t *rangelist = apr_hash_this_val(hi);
      const char *path;

      merge_source = svn_relpath_canonicalize(merge_source, pool);

      /* The svn:mergeinfo property syntax demands a repos abspath */
      path = svn_fspath__canonicalize(svn_relpath_join(parent_dir,
                                                       merge_source, pool),
                                      pool);
      svn_hash_sets(prefixed_mergeinfo, path, rangelist);
    }
  return svn_mergeinfo_to_string(mergeinfo_val, prefixed_mergeinfo, pool);
}