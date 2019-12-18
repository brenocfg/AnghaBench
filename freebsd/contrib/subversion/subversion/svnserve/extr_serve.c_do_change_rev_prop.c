#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_svn_conn_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_12__ {TYPE_2__* client_info; TYPE_1__* repository; } ;
typedef  TYPE_3__ server_baton_t ;
struct TYPE_13__ {int /*<<< orphan*/ * conn; TYPE_3__* server; } ;
typedef  TYPE_4__ authz_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_11__ {int /*<<< orphan*/  user; } ;
struct TYPE_10__ {int /*<<< orphan*/  repos; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_CMD_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  authz_check_access_cb_func (TYPE_3__*) ; 
 int /*<<< orphan*/  log_command (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  must_have_access (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_authz_write ; 
 int /*<<< orphan*/  svn_log__change_rev_prop (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_svn__write_cmd_response (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  svn_repos_fs_change_rev_prop4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/  const* const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *do_change_rev_prop(svn_ra_svn_conn_t *conn,
                                       server_baton_t *b,
                                       svn_revnum_t rev,
                                       const char *name,
                                       const svn_string_t *const *old_value_p,
                                       const svn_string_t *value,
                                       apr_pool_t *pool)
{
  authz_baton_t ab;

  ab.server = b;
  ab.conn = conn;

  SVN_ERR(must_have_access(conn, pool, b, svn_authz_write, NULL, FALSE));
  SVN_ERR(log_command(b, conn, pool, "%s",
                      svn_log__change_rev_prop(rev, name, pool)));
  SVN_CMD_ERR(svn_repos_fs_change_rev_prop4(b->repository->repos, rev,
                                            b->client_info->user,
                                            name, old_value_p, value,
                                            TRUE, TRUE,
                                            authz_check_access_cb_func(b), &ab,
                                            pool));
  SVN_ERR(svn_ra_svn__write_cmd_response(conn, pool, ""));

  return SVN_NO_ERROR;
}