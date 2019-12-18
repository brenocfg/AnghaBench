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
typedef  int /*<<< orphan*/  svn_opt_revision_t ;
struct TYPE_4__ {int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
typedef  TYPE_1__ svn_opt_revision_range_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 TYPE_1__* apr_palloc (int /*<<< orphan*/ *,int) ; 

svn_opt_revision_range_t *
svn_opt__revision_range_create(const svn_opt_revision_t *start_revision,
                               const svn_opt_revision_t *end_revision,
                               apr_pool_t *result_pool)
{
  svn_opt_revision_range_t *range = apr_palloc(result_pool, sizeof(*range));

  range->start = *start_revision;
  range->end = *end_revision;
  return range;
}