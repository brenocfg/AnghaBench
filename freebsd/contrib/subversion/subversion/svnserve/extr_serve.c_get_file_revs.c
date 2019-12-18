#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_svn_conn_t ;
typedef  int /*<<< orphan*/  svn_ra_svn__list_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_13__ {TYPE_2__* repository; } ;
typedef  TYPE_3__ server_baton_t ;
struct TYPE_14__ {int /*<<< orphan*/ * pool; int /*<<< orphan*/ * conn; } ;
typedef  TYPE_4__ file_revs_baton_t ;
struct TYPE_15__ {int /*<<< orphan*/ * conn; TYPE_3__* server; } ;
typedef  TYPE_5__ authz_baton_t ;
typedef  scalar_t__ apr_uint64_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_12__ {int /*<<< orphan*/  repos; TYPE_1__* fs_path; } ;
struct TYPE_11__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_CMD_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ SVN_RA_SVN_UNSPECIFIED_NUMBER ; 
 int /*<<< orphan*/  authz_check_access_cb_func (TYPE_3__*) ; 
 int /*<<< orphan*/  file_rev_handler ; 
 int /*<<< orphan*/  log_command (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 
 char* svn_fspath__join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_log__get_file_revs (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_svn__parse_tuple (int /*<<< orphan*/ *,char*,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  svn_ra_svn__write_cmd_response (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * svn_ra_svn__write_word (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 char* svn_relpath_canonicalize (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_repos_get_file_revs2 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trivial_auth_request (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static svn_error_t *
get_file_revs(svn_ra_svn_conn_t *conn,
              apr_pool_t *pool,
              svn_ra_svn__list_t *params,
              void *baton)
{
  server_baton_t *b = baton;
  svn_error_t *err, *write_err;
  file_revs_baton_t frb;
  svn_revnum_t start_rev, end_rev;
  const char *path;
  const char *full_path;
  apr_uint64_t include_merged_revs_param;
  svn_boolean_t include_merged_revisions;
  authz_baton_t ab;

  ab.server = b;
  ab.conn = conn;

  /* Parse arguments. */
  SVN_ERR(svn_ra_svn__parse_tuple(params, "c(?r)(?r)?B",
                                  &path, &start_rev, &end_rev,
                                  &include_merged_revs_param));
  path = svn_relpath_canonicalize(path, pool);
  SVN_ERR(trivial_auth_request(conn, pool, b));
  full_path = svn_fspath__join(b->repository->fs_path->data, path, pool);

  if (include_merged_revs_param == SVN_RA_SVN_UNSPECIFIED_NUMBER)
    include_merged_revisions = FALSE;
  else
    include_merged_revisions = (svn_boolean_t) include_merged_revs_param;

  SVN_ERR(log_command(b, conn, pool, "%s",
                      svn_log__get_file_revs(full_path, start_rev, end_rev,
                                             include_merged_revisions,
                                             pool)));

  frb.conn = conn;
  frb.pool = NULL;

  err = svn_repos_get_file_revs2(b->repository->repos, full_path, start_rev,
                                 end_rev, include_merged_revisions,
                                 authz_check_access_cb_func(b), &ab,
                                 file_rev_handler, &frb, pool);
  write_err = svn_ra_svn__write_word(conn, pool, "done");
  if (write_err)
    {
      svn_error_clear(err);
      return write_err;
    }
  SVN_CMD_ERR(err);
  SVN_ERR(svn_ra_svn__write_cmd_response(conn, pool, ""));

  return SVN_NO_ERROR;
}