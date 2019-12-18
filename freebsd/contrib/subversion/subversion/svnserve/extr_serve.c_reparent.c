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
typedef  int /*<<< orphan*/  svn_ra_svn_conn_t ;
typedef  int /*<<< orphan*/  svn_ra_svn__list_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_6__ {TYPE_1__* repository; } ;
typedef  TYPE_2__ server_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_5__ {char const* repos_url; int /*<<< orphan*/  fs_path; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_CMD_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  get_fs_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  log_command (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_log__reparent (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_path_uri_decode (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_svn__parse_tuple (int /*<<< orphan*/ *,char*,char const**) ; 
 int /*<<< orphan*/  svn_ra_svn__write_cmd_response (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  svn_stringbuf_set (int /*<<< orphan*/ ,char const*) ; 
 char* svn_uri_canonicalize (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trivial_auth_request (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static svn_error_t *
reparent(svn_ra_svn_conn_t *conn,
         apr_pool_t *pool,
         svn_ra_svn__list_t *params,
         void *baton)
{
  server_baton_t *b = baton;
  const char *url;
  const char *fs_path;

  SVN_ERR(svn_ra_svn__parse_tuple(params, "c", &url));
  url = svn_uri_canonicalize(url, pool);
  SVN_ERR(trivial_auth_request(conn, pool, b));
  SVN_CMD_ERR(get_fs_path(svn_path_uri_decode(b->repository->repos_url, pool),
                          svn_path_uri_decode(url, pool),
                          &fs_path));
  SVN_ERR(log_command(b, conn, pool, "%s", svn_log__reparent(fs_path, pool)));
  svn_stringbuf_set(b->repository->fs_path, fs_path);
  SVN_ERR(svn_ra_svn__write_cmd_response(conn, pool, ""));
  return SVN_NO_ERROR;
}