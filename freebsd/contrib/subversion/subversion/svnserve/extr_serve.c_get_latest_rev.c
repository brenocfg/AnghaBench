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
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_svn_conn_t ;
typedef  int /*<<< orphan*/  svn_ra_svn__list_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_6__ {TYPE_1__* repository; } ;
typedef  TYPE_2__ server_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_5__ {int /*<<< orphan*/  fs; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_CMD_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  log_command (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  svn_fs_youngest_rev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_svn__write_cmd_response (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trivial_auth_request (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static svn_error_t *
get_latest_rev(svn_ra_svn_conn_t *conn,
               apr_pool_t *pool,
               svn_ra_svn__list_t *params,
               void *baton)
{
  server_baton_t *b = baton;
  svn_revnum_t rev;

  SVN_ERR(log_command(b, conn, pool, "get-latest-rev"));

  SVN_ERR(trivial_auth_request(conn, pool, b));
  SVN_CMD_ERR(svn_fs_youngest_rev(&rev, b->repository->fs, pool));
  SVN_ERR(svn_ra_svn__write_cmd_response(conn, pool, "r", rev));
  return SVN_NO_ERROR;
}