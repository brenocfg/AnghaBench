#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_6__ {TYPE_1__* vtable; } ;
typedef  TYPE_2__ svn_branch__state_t ;
typedef  int /*<<< orphan*/  svn_branch__rev_bid_eid_t ;
typedef  int /*<<< orphan*/  svn_branch__eid_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* copy_tree ) (TYPE_2__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_branch__state_copy_tree(svn_branch__state_t *branch,
                            const svn_branch__rev_bid_eid_t *src_el_rev,
                            svn_branch__eid_t new_parent_eid,
                            const char *new_name,
                            apr_pool_t *scratch_pool)
{
  SVN_ERR(branch->vtable->copy_tree(branch,
                                    src_el_rev, new_parent_eid, new_name,
                                    scratch_pool));
  return SVN_NO_ERROR;
}