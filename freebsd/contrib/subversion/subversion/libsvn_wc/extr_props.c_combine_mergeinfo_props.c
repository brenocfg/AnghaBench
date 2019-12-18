#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_mergeinfo_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_mergeinfo_merge2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_mergeinfo_parse (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_mergeinfo_to_string (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
combine_mergeinfo_props(const svn_string_t **output,
                        const svn_string_t *prop_val1,
                        const svn_string_t *prop_val2,
                        apr_pool_t *result_pool,
                        apr_pool_t *scratch_pool)
{
  svn_mergeinfo_t mergeinfo1, mergeinfo2;
  svn_string_t *mergeinfo_string;

  SVN_ERR(svn_mergeinfo_parse(&mergeinfo1, prop_val1->data, scratch_pool));
  SVN_ERR(svn_mergeinfo_parse(&mergeinfo2, prop_val2->data, scratch_pool));
  SVN_ERR(svn_mergeinfo_merge2(mergeinfo1, mergeinfo2, scratch_pool,
                               scratch_pool));
  SVN_ERR(svn_mergeinfo_to_string(&mergeinfo_string, mergeinfo1, result_pool));
  *output = mergeinfo_string;
  return SVN_NO_ERROR;
}