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
struct TYPE_5__ {int /*<<< orphan*/  subbranches; } ;
typedef  TYPE_1__ svn_branch__subtree_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 TYPE_1__* svn_eid__hash_get (int /*<<< orphan*/ ,int) ; 

svn_branch__subtree_t *
svn_branch__subtree_get_subbranch_at_eid(svn_branch__subtree_t *subtree,
                                         int eid,
                                         apr_pool_t *result_pool)
{
  subtree = svn_eid__hash_get(subtree->subbranches, eid);

  return subtree;
}