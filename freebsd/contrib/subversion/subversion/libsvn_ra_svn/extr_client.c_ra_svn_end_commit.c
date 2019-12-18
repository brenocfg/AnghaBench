#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_7__ {int /*<<< orphan*/  repos_root; int /*<<< orphan*/  post_commit_err; int /*<<< orphan*/  author; int /*<<< orphan*/  date; int /*<<< orphan*/  revision; } ;
typedef  TYPE_1__ svn_commit_info_t ;
struct TYPE_8__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  callback_baton; int /*<<< orphan*/  (* callback ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;TYPE_6__* sess_baton; } ;
typedef  TYPE_2__ ra_svn_commit_callback_baton_t ;
struct TYPE_10__ {TYPE_3__* conn; } ;
struct TYPE_9__ {int /*<<< orphan*/  repos_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_auth_request (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* svn_create_commit_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_ra_svn__read_tuple (TYPE_3__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *ra_svn_end_commit(void *baton)
{
  ra_svn_commit_callback_baton_t *ccb = baton;
  svn_commit_info_t *commit_info = svn_create_commit_info(ccb->pool);

  SVN_ERR(handle_auth_request(ccb->sess_baton, ccb->pool));
  SVN_ERR(svn_ra_svn__read_tuple(ccb->sess_baton->conn, ccb->pool,
                                 "r(?c)(?c)?(?c)",
                                 &(commit_info->revision),
                                 &(commit_info->date),
                                 &(commit_info->author),
                                 &(commit_info->post_commit_err)));

  commit_info->repos_root = apr_pstrdup(ccb->pool,
                                        ccb->sess_baton->conn->repos_root);

  if (ccb->callback)
    SVN_ERR(ccb->callback(commit_info, ccb->callback_baton, ccb->pool));

  return SVN_NO_ERROR;
}