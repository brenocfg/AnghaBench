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
typedef  int /*<<< orphan*/  svn_ra_svn_conn_t ;
typedef  int /*<<< orphan*/  svn_ra_svn__list_t ;
typedef  int /*<<< orphan*/  svn_lock_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_depth_t ;
struct TYPE_12__ {TYPE_2__* repository; } ;
typedef  TYPE_3__ server_baton_t ;
struct TYPE_13__ {int /*<<< orphan*/ * conn; TYPE_3__* server; } ;
typedef  TYPE_4__ authz_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;
struct TYPE_11__ {int /*<<< orphan*/  repos; TYPE_1__* fs_path; } ;
struct TYPE_10__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_CMD_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_INCORRECT_PARAMS ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_this_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  authz_check_access_cb_func (TYPE_3__*) ; 
 int /*<<< orphan*/  log_command (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * log_fail_and_flush (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_depth_empty ; 
 scalar_t__ svn_depth_files ; 
 scalar_t__ svn_depth_from_word (char const*) ; 
 scalar_t__ svn_depth_immediates ; 
 scalar_t__ svn_depth_infinity ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 char* svn_fspath__join (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_path_uri_encode (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_svn__parse_tuple (int /*<<< orphan*/ *,char*,char const**,char const**) ; 
 int /*<<< orphan*/  svn_ra_svn__write_tuple (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  svn_relpath_canonicalize (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos_fs_get_locks2 (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,scalar_t__,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trivial_auth_request (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_locks(svn_ra_svn_conn_t *conn,
          apr_pool_t *pool,
          svn_ra_svn__list_t *params,
          void *baton)
{
  server_baton_t *b = baton;
  const char *path;
  const char *full_path;
  const char *depth_word;
  svn_depth_t depth;
  apr_hash_t *locks;
  apr_hash_index_t *hi;
  svn_error_t *err;
  authz_baton_t ab;

  ab.server = b;
  ab.conn = conn;

  SVN_ERR(svn_ra_svn__parse_tuple(params, "c?(?w)", &path, &depth_word));

  depth = depth_word ? svn_depth_from_word(depth_word) : svn_depth_infinity;
  if ((depth != svn_depth_empty) &&
      (depth != svn_depth_files) &&
      (depth != svn_depth_immediates) &&
      (depth != svn_depth_infinity))
    {
      err = svn_error_create(SVN_ERR_INCORRECT_PARAMS, NULL,
                             "Invalid 'depth' specified in get-locks request");
      return log_fail_and_flush(err, b, conn, pool);
    }

  full_path = svn_fspath__join(b->repository->fs_path->data,
                               svn_relpath_canonicalize(path, pool), pool);

  SVN_ERR(trivial_auth_request(conn, pool, b));

  SVN_ERR(log_command(b, conn, pool, "get-locks %s",
                      svn_path_uri_encode(full_path, pool)));
  SVN_CMD_ERR(svn_repos_fs_get_locks2(&locks, b->repository->repos,
                                      full_path, depth,
                                      authz_check_access_cb_func(b), &ab,
                                      pool));

  SVN_ERR(svn_ra_svn__write_tuple(conn, pool, "w((!", "success"));
  for (hi = apr_hash_first(pool, locks); hi; hi = apr_hash_next(hi))
    {
      svn_lock_t *l = apr_hash_this_val(hi);

      SVN_ERR(write_lock(conn, pool, l));
    }
  SVN_ERR(svn_ra_svn__write_tuple(conn, pool, "!))"));

  return SVN_NO_ERROR;
}