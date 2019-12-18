#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_svn_conn_t ;
typedef  int /*<<< orphan*/  svn_ra_svn__list_t ;
typedef  int /*<<< orphan*/  svn_lock_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_8__ {TYPE_2__* repository; } ;
typedef  TYPE_3__ server_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_7__ {int /*<<< orphan*/  repos; TYPE_1__* fs_path; } ;
struct TYPE_6__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_CMD_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  log_command (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  must_have_access (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_authz_write ; 
 char* svn_fspath__join (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_log__lock_one_path (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_svn__parse_tuple (int /*<<< orphan*/ *,char*,char const**,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_svn__write_tuple (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  svn_relpath_canonicalize (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos_fs_lock (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
lock(svn_ra_svn_conn_t *conn,
     apr_pool_t *pool,
     svn_ra_svn__list_t *params,
     void *baton)
{
  server_baton_t *b = baton;
  const char *path;
  const char *comment;
  const char *full_path;
  svn_boolean_t steal_lock;
  svn_revnum_t current_rev;
  svn_lock_t *l;

  SVN_ERR(svn_ra_svn__parse_tuple(params, "c(?c)b(?r)", &path, &comment,
                                  &steal_lock, &current_rev));
  full_path = svn_fspath__join(b->repository->fs_path->data,
                               svn_relpath_canonicalize(path, pool), pool);

  SVN_ERR(must_have_access(conn, pool, b, svn_authz_write,
                           full_path, TRUE));
  SVN_ERR(log_command(b, conn, pool, "%s",
                      svn_log__lock_one_path(full_path, steal_lock, pool)));

  SVN_CMD_ERR(svn_repos_fs_lock(&l, b->repository->repos, full_path, NULL,
                                comment, 0, 0, /* No expiration time. */
                                current_rev, steal_lock, pool));

  SVN_ERR(svn_ra_svn__write_tuple(conn, pool, "w(!", "success"));
  SVN_ERR(write_lock(conn, pool, l));
  SVN_ERR(svn_ra_svn__write_tuple(conn, pool, "!)"));

  return SVN_NO_ERROR;
}