#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  relpath; int /*<<< orphan*/  rev; } ;
typedef  TYPE_1__ svn_pathrev_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_8__ {int /*<<< orphan*/  eid; int /*<<< orphan*/  branch_id; int /*<<< orphan*/  rev; } ;
typedef  TYPE_2__ svn_element__branch_ref_t ;
typedef  int /*<<< orphan*/  svn_branch__repos_t ;
struct TYPE_9__ {int /*<<< orphan*/  eid; int /*<<< orphan*/  branch; int /*<<< orphan*/  rev; } ;
typedef  TYPE_3__ svn_branch__el_rev_id_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  branch_get_storage_rrpath_by_eid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_branch__repos_find_el_rev_by_id (TYPE_3__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
storage_pathrev_from_branch_ref(svn_pathrev_t *storage_pathrev_p,
                                svn_element__branch_ref_t branch_ref,
                                svn_branch__repos_t *repos,
                                apr_pool_t *result_pool,
                                apr_pool_t *scratch_pool)
{
  svn_branch__el_rev_id_t *el_rev;

  SVN_ERR(svn_branch__repos_find_el_rev_by_id(&el_rev,
                                              repos,
                                              branch_ref.rev,
                                              branch_ref.branch_id,
                                              branch_ref.eid,
                                              scratch_pool, scratch_pool));

  storage_pathrev_p->rev = el_rev->rev;
  storage_pathrev_p->relpath
    = branch_get_storage_rrpath_by_eid(el_rev->branch, el_rev->eid,
                                       result_pool);

  return SVN_NO_ERROR;
}