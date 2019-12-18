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
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_8__ {TYPE_2__* repository; } ;
typedef  TYPE_3__ server_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_7__ {int /*<<< orphan*/  fs; TYPE_1__* fs_path; } ;
struct TYPE_6__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  log_command (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 char* svn_fspath__join (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_svn__parse_tuple (int /*<<< orphan*/ *,char*,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_svn__write_cmd_response (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_relpath_canonicalize (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos_deleted_rev (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trivial_auth_request (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static svn_error_t *
get_deleted_rev(svn_ra_svn_conn_t *conn,
                apr_pool_t *pool,
                svn_ra_svn__list_t *params,
                void *baton)
{
  server_baton_t *b = baton;
  const char *path, *full_path;
  svn_revnum_t peg_revision;
  svn_revnum_t end_revision;
  svn_revnum_t revision_deleted;

  SVN_ERR(svn_ra_svn__parse_tuple(params, "crr",
                                 &path, &peg_revision, &end_revision));
  full_path = svn_fspath__join(b->repository->fs_path->data,
                               svn_relpath_canonicalize(path, pool), pool);
  SVN_ERR(log_command(b, conn, pool, "get-deleted-rev"));
  SVN_ERR(trivial_auth_request(conn, pool, b));
  SVN_ERR(svn_repos_deleted_rev(b->repository->fs, full_path, peg_revision,
                                end_revision, &revision_deleted, pool));
  SVN_ERR(svn_ra_svn__write_cmd_response(conn, pool, "r", revision_deleted));
  return SVN_NO_ERROR;
}