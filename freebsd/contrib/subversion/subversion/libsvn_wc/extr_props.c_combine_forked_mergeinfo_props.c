#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_mergeinfo_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  diff_mergeinfo_props (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__ const*,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_mergeinfo_merge2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_mergeinfo_parse (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_mergeinfo_remove2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_mergeinfo_to_string (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
combine_forked_mergeinfo_props(const svn_string_t **output,
                               const svn_string_t *from_prop_val,
                               const svn_string_t *working_prop_val,
                               const svn_string_t *to_prop_val,
                               apr_pool_t *result_pool,
                               apr_pool_t *scratch_pool)
{
  svn_mergeinfo_t from_mergeinfo, l_deleted, l_added, r_deleted, r_added;
  svn_string_t *mergeinfo_string;

  /* ### OPTIMIZE: Use from_mergeinfo when diff'ing. */
  SVN_ERR(diff_mergeinfo_props(&l_deleted, &l_added, from_prop_val,
                               working_prop_val, scratch_pool));
  SVN_ERR(diff_mergeinfo_props(&r_deleted, &r_added, from_prop_val,
                               to_prop_val, scratch_pool));
  SVN_ERR(svn_mergeinfo_merge2(l_deleted, r_deleted,
                               scratch_pool, scratch_pool));
  SVN_ERR(svn_mergeinfo_merge2(l_added, r_added,
                               scratch_pool, scratch_pool));

  /* Apply the combined deltas to the base. */
  SVN_ERR(svn_mergeinfo_parse(&from_mergeinfo, from_prop_val->data,
                              scratch_pool));
  SVN_ERR(svn_mergeinfo_merge2(from_mergeinfo, l_added,
                               scratch_pool, scratch_pool));

  SVN_ERR(svn_mergeinfo_remove2(&from_mergeinfo, l_deleted, from_mergeinfo,
                                TRUE, scratch_pool, scratch_pool));

  SVN_ERR(svn_mergeinfo_to_string(&mergeinfo_string, from_mergeinfo,
                                  result_pool));
  *output = mergeinfo_string;
  return SVN_NO_ERROR;
}