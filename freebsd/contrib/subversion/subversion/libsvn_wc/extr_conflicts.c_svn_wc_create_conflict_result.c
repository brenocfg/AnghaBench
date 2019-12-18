#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * merged_value; int /*<<< orphan*/  save_merged; int /*<<< orphan*/  merged_file; int /*<<< orphan*/  choice; } ;
typedef  TYPE_1__ svn_wc_conflict_result_t ;
typedef  int /*<<< orphan*/  svn_wc_conflict_choice_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 

svn_wc_conflict_result_t *
svn_wc_create_conflict_result(svn_wc_conflict_choice_t choice,
                              const char *merged_file,
                              apr_pool_t *pool)
{
  svn_wc_conflict_result_t *result = apr_pcalloc(pool, sizeof(*result));
  result->choice = choice;
  result->merged_file = apr_pstrdup(pool, merged_file);
  result->save_merged = FALSE;
  result->merged_value = NULL;

  /* If we add more fields to svn_wc_conflict_result_t, add them here. */

  return result;
}