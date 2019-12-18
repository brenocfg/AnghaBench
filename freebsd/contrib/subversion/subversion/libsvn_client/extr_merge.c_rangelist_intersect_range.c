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
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_rangelist_t ;
typedef  int /*<<< orphan*/  svn_merge_range_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * apr_array_make (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * svn_rangelist__initialize (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_rangelist_intersect (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
rangelist_intersect_range(svn_rangelist_t **out_rangelist,
                          const svn_rangelist_t *in_rangelist,
                          svn_revnum_t rev1,
                          svn_revnum_t rev2,
                          svn_boolean_t consider_inheritance,
                          apr_pool_t *result_pool,
                          apr_pool_t *scratch_pool)
{
  SVN_ERR_ASSERT(rev1 <= rev2);

  if (rev1 < rev2)
    {
      svn_rangelist_t *simple_rangelist =
        svn_rangelist__initialize(rev1, rev2, TRUE, scratch_pool);

      SVN_ERR(svn_rangelist_intersect(out_rangelist,
                                      simple_rangelist, in_rangelist,
                                      consider_inheritance, result_pool));
    }
  else
    {
      *out_rangelist = apr_array_make(result_pool, 0,
                                      sizeof(svn_merge_range_t *));
    }
  return SVN_NO_ERROR;
}