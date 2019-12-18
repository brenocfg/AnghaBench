#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_svn_conn_t ;
typedef  int /*<<< orphan*/  svn_ra_svn__list_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_11__ {TYPE_2__* repository; } ;
typedef  TYPE_3__ server_baton_t ;
struct TYPE_12__ {int /*<<< orphan*/ * conn; TYPE_3__* server; } ;
typedef  TYPE_4__ authz_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_10__ {int /*<<< orphan*/  repos; int /*<<< orphan*/  fs; TYPE_1__* fs_path; } ;
struct TYPE_9__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_CMD_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_NO_SUCH_REVISION ; 
 int /*<<< orphan*/  SVN_IS_VALID_REVNUM (scalar_t__) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  authz_check_access_cb_func (TYPE_3__*) ; 
 int /*<<< orphan*/  gls_receiver ; 
 int /*<<< orphan*/  log_command (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * log_fail_and_flush (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_compose_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * svn_fs_youngest_rev (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* svn_fspath__join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_log__get_location_segments (char const*,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_svn__parse_tuple (int /*<<< orphan*/ *,char*,char const**,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  svn_ra_svn__write_cmd_response (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * svn_ra_svn__write_word (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 char* svn_relpath_canonicalize (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_repos_node_location_segments (int /*<<< orphan*/ ,char const*,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trivial_auth_request (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static svn_error_t *
get_location_segments(svn_ra_svn_conn_t *conn,
                      apr_pool_t *pool,
                      svn_ra_svn__list_t *params,
                      void *baton)
{
  svn_error_t *err, *write_err;
  server_baton_t *b = baton;
  svn_revnum_t peg_revision, start_rev, end_rev;
  const char *relative_path;
  const char *abs_path;
  authz_baton_t ab;

  ab.server = b;
  ab.conn = conn;

  /* Parse the arguments. */
  SVN_ERR(svn_ra_svn__parse_tuple(params, "c(?r)(?r)(?r)",
                                  &relative_path, &peg_revision,
                                  &start_rev, &end_rev));
  relative_path = svn_relpath_canonicalize(relative_path, pool);

  abs_path = svn_fspath__join(b->repository->fs_path->data, relative_path,
                              pool);

  SVN_ERR(trivial_auth_request(conn, pool, b));
  SVN_ERR(log_command(baton, conn, pool, "%s",
                      svn_log__get_location_segments(abs_path, peg_revision,
                                                     start_rev, end_rev,
                                                     pool)));

  /* No START_REV or PEG_REVISION?  We'll use HEAD. */
  if (!SVN_IS_VALID_REVNUM(start_rev) || !SVN_IS_VALID_REVNUM(peg_revision))
    {
      svn_revnum_t youngest;

      err = svn_fs_youngest_rev(&youngest, b->repository->fs, pool);

      if (err)
        {
          err = svn_error_compose_create(
                    svn_ra_svn__write_word(conn, pool, "done"),
                    err);

          return log_fail_and_flush(err, b, conn, pool);
        }

      if (!SVN_IS_VALID_REVNUM(start_rev))
        start_rev = youngest;
      if (!SVN_IS_VALID_REVNUM(peg_revision))
        peg_revision = youngest;
    }

  /* No END_REV?  We'll use 0. */
  if (!SVN_IS_VALID_REVNUM(end_rev))
    end_rev = 0;

  if (end_rev > start_rev)
    {
      err = svn_ra_svn__write_word(conn, pool, "done");
      err = svn_error_createf(SVN_ERR_FS_NO_SUCH_REVISION, err,
                              "Get-location-segments end revision must not be "
                              "younger than start revision");
      return log_fail_and_flush(err, b, conn, pool);
    }

  if (start_rev > peg_revision)
    {
      err = svn_ra_svn__write_word(conn, pool, "done");
      err = svn_error_createf(SVN_ERR_FS_NO_SUCH_REVISION, err,
                              "Get-location-segments start revision must not "
                              "be younger than peg revision");
      return log_fail_and_flush(err, b, conn, pool);
    }

  /* All the parameters are fine - let's perform the query against the
   * repository. */

  /* We store both err and write_err here, so the client will get
   * the "done" even if there was an error in fetching the results. */

  err = svn_repos_node_location_segments(b->repository->repos, abs_path,
                                         peg_revision, start_rev, end_rev,
                                         gls_receiver, (void *)conn,
                                         authz_check_access_cb_func(b), &ab,
                                         pool);
  write_err = svn_ra_svn__write_word(conn, pool, "done");
  if (write_err)
    {
      return svn_error_compose_create(write_err, err);
    }
  SVN_CMD_ERR(err);

  SVN_ERR(svn_ra_svn__write_cmd_response(conn, pool, ""));

  return SVN_NO_ERROR;
}