#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_svn_conn_t ;
typedef  int /*<<< orphan*/  svn_ra_svn__list_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_9__ {TYPE_1__* repository; } ;
typedef  TYPE_2__ server_baton_t ;
struct TYPE_10__ {int /*<<< orphan*/ * conn; TYPE_2__* server; } ;
typedef  TYPE_3__ authz_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
struct TYPE_8__ {int /*<<< orphan*/  repos; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_CMD_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  authz_check_access_cb_func (TYPE_2__*) ; 
 int /*<<< orphan*/  log_command (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_log__rev_proplist (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_svn__parse_tuple (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_svn__write_proplist (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_svn__write_tuple (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  svn_repos_fs_revision_proplist (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trivial_auth_request (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static svn_error_t *
rev_proplist(svn_ra_svn_conn_t *conn,
             apr_pool_t *pool,
             svn_ra_svn__list_t *params,
             void *baton)
{
  server_baton_t *b = baton;
  svn_revnum_t rev;
  apr_hash_t *props;
  authz_baton_t ab;

  ab.server = b;
  ab.conn = conn;

  SVN_ERR(svn_ra_svn__parse_tuple(params, "r", &rev));
  SVN_ERR(log_command(b, conn, pool, "%s", svn_log__rev_proplist(rev, pool)));

  SVN_ERR(trivial_auth_request(conn, pool, b));
  SVN_CMD_ERR(svn_repos_fs_revision_proplist(&props, b->repository->repos,
                                             rev,
                                             authz_check_access_cb_func(b),
                                             &ab, pool));
  SVN_ERR(svn_ra_svn__write_tuple(conn, pool, "w((!", "success"));
  SVN_ERR(svn_ra_svn__write_proplist(conn, pool, props));
  SVN_ERR(svn_ra_svn__write_tuple(conn, pool, "!))"));
  return SVN_NO_ERROR;
}