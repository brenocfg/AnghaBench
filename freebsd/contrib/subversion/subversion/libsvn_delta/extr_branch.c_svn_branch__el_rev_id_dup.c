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
struct TYPE_5__ {int /*<<< orphan*/  rev; int /*<<< orphan*/  eid; int /*<<< orphan*/  branch; } ;
typedef  TYPE_1__ svn_branch__el_rev_id_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 TYPE_1__* svn_branch__el_rev_id_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_branch__el_rev_id_t *
svn_branch__el_rev_id_dup(const svn_branch__el_rev_id_t *old_id,
                          apr_pool_t *result_pool)
{
  if (! old_id)
    return NULL;

  return svn_branch__el_rev_id_create(old_id->branch,
                                      old_id->eid,
                                      old_id->rev,
                                      result_pool);
}