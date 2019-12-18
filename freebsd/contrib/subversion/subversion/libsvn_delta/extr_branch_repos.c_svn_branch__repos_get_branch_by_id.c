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
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_branch__txn_t ;
typedef  int /*<<< orphan*/  svn_branch__state_t ;
struct TYPE_6__ {TYPE_1__* rev_roots; } ;
typedef  TYPE_2__ svn_branch__repos_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_5__ {scalar_t__ nelts; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_BRANCH__ERR ; 
 int /*<<< orphan*/  SVN_ERR_FS_NO_SUCH_REVISION ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * svn_branch__repos_get_revision (TYPE_2__ const*,scalar_t__) ; 
 int /*<<< orphan*/ * svn_branch__txn_get_branch_by_id (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,...) ; 

svn_error_t *
svn_branch__repos_get_branch_by_id(svn_branch__state_t **branch_p,
                                   const svn_branch__repos_t *repos,
                                   svn_revnum_t revnum,
                                   const char *branch_id,
                                   apr_pool_t *scratch_pool)
{
  svn_branch__txn_t *rev_root;

  if (revnum < 0 || revnum >= repos->rev_roots->nelts)
    return svn_error_createf(SVN_ERR_FS_NO_SUCH_REVISION, NULL,
                             _("No such revision %ld"), revnum);

  rev_root = svn_branch__repos_get_revision(repos, revnum);
  *branch_p = svn_branch__txn_get_branch_by_id(rev_root, branch_id,
                                               scratch_pool);
  if (! *branch_p)
    return svn_error_createf(SVN_BRANCH__ERR, NULL,
                             _("Branch %s not found in r%ld"),
                             branch_id, revnum);
  return SVN_NO_ERROR;
}