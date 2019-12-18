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
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_6__ {int /*<<< orphan*/  repos_root; } ;
typedef  TYPE_1__ svn_commit_info_t ;
struct ccw_baton {int /*<<< orphan*/  original_baton; int /*<<< orphan*/  (* original_callback ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  session; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_commit_info_dup (TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_ra_local__get_repos_root (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
commit_callback_wrapper(const svn_commit_info_t *commit_info,
                        void *baton,
                        apr_pool_t *scratch_pool)
{
  struct ccw_baton *ccwb = baton;
  svn_commit_info_t *ci = svn_commit_info_dup(commit_info, scratch_pool);

  SVN_ERR(svn_ra_local__get_repos_root(ccwb->session, &ci->repos_root,
                                       scratch_pool));

  return svn_error_trace(ccwb->original_callback(ci, ccwb->original_baton,
                                                 scratch_pool));
}