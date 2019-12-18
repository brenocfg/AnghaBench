#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ nelts; } ;
typedef  TYPE_1__ svn_rangelist_t ;
typedef  int /*<<< orphan*/  svn_mergeinfo_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 TYPE_1__* apr_hash_this_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 TYPE_1__* svn_hash_gets (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_rangelist_dup (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_rangelist_intersect (TYPE_1__**,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_mergeinfo_intersect2(svn_mergeinfo_t *mergeinfo,
                         svn_mergeinfo_t mergeinfo1,
                         svn_mergeinfo_t mergeinfo2,
                         svn_boolean_t consider_inheritance,
                         apr_pool_t *result_pool,
                         apr_pool_t *scratch_pool)
{
  apr_hash_index_t *hi;
  apr_pool_t *iterpool;

  *mergeinfo = apr_hash_make(result_pool);
  iterpool = svn_pool_create(scratch_pool);

  /* ### TODO(reint): Do we care about the case when a path in one
     ### mergeinfo hash has inheritable mergeinfo, and in the other
     ### has non-inheritable mergeinfo?  It seems like that path
     ### itself should really be an intersection, while child paths
     ### should not be... */
  for (hi = apr_hash_first(scratch_pool, mergeinfo1);
       hi; hi = apr_hash_next(hi))
    {
      const char *path = apr_hash_this_key(hi);
      svn_rangelist_t *rangelist1 = apr_hash_this_val(hi);
      svn_rangelist_t *rangelist2;

      svn_pool_clear(iterpool);
      rangelist2 = svn_hash_gets(mergeinfo2, path);
      if (rangelist2)
        {
          SVN_ERR(svn_rangelist_intersect(&rangelist2, rangelist1, rangelist2,
                                          consider_inheritance, iterpool));
          if (rangelist2->nelts > 0)
            svn_hash_sets(*mergeinfo, apr_pstrdup(result_pool, path),
                          svn_rangelist_dup(rangelist2, result_pool));
        }
    }
  svn_pool_destroy(iterpool);
  return SVN_NO_ERROR;
}