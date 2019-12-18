#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_tristate_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_svn_conn_t ;
typedef  int /*<<< orphan*/  svn_ra_svn__list_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_9__ {TYPE_2__* repository; } ;
typedef  TYPE_3__ server_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_8__ {char const* repos_url; TYPE_1__* fs_path; int /*<<< orphan*/  fs; } ;
struct TYPE_7__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_CMD_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_DEPTH_INFINITY_OR_FILES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * accept_report (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  get_fs_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  log_command (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_depth_from_word (char const*) ; 
 int /*<<< orphan*/  svn_depth_unknown ; 
 int /*<<< orphan*/  svn_fs_youngest_rev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* svn_fspath__join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_log__switch (char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_path_uri_decode (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_svn__parse_tuple (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *,char const**,char const**,scalar_t__*,scalar_t__*) ; 
 char* svn_relpath_canonicalize (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_tristate_false ; 
 scalar_t__ svn_tristate_true ; 
 char* svn_uri_canonicalize (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trivial_auth_request (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static svn_error_t *
switch_cmd(svn_ra_svn_conn_t *conn,
           apr_pool_t *pool,
           svn_ra_svn__list_t *params,
           void *baton)
{
  server_baton_t *b = baton;
  svn_revnum_t rev;
  const char *target, *depth_word;
  const char *switch_url, *switch_path;
  svn_boolean_t recurse;
  /* Default to unknown.  Old clients won't send depth, but we'll
     handle that by converting recurse if necessary. */
  svn_depth_t depth = svn_depth_unknown;
  svn_tristate_t send_copyfrom_args; /* Optional; default FALSE */
  svn_tristate_t ignore_ancestry; /* Optional; default TRUE */

  /* Parse the arguments. */
  SVN_ERR(svn_ra_svn__parse_tuple(params, "(?r)cbc?w?33", &rev, &target,
                                  &recurse, &switch_url, &depth_word,
                                  &send_copyfrom_args, &ignore_ancestry));
  target = svn_relpath_canonicalize(target, pool);
  switch_url = svn_uri_canonicalize(switch_url, pool);

  if (depth_word)
    depth = svn_depth_from_word(depth_word);
  else
    depth = SVN_DEPTH_INFINITY_OR_FILES(recurse);

  SVN_ERR(trivial_auth_request(conn, pool, b));
  if (!SVN_IS_VALID_REVNUM(rev))
    SVN_CMD_ERR(svn_fs_youngest_rev(&rev, b->repository->fs, pool));

  SVN_CMD_ERR(get_fs_path(svn_path_uri_decode(b->repository->repos_url,
                                              pool),
                          svn_path_uri_decode(switch_url, pool),
                          &switch_path));

  {
    const char *full_path = svn_fspath__join(b->repository->fs_path->data,
                                             target, pool);
    SVN_ERR(log_command(b, conn, pool, "%s",
                        svn_log__switch(full_path, switch_path, rev,
                                        depth, pool)));
  }

  return accept_report(NULL, NULL,
                       conn, pool, b, rev, target, switch_path, TRUE,
                       depth,
                       (send_copyfrom_args == svn_tristate_true),
                       (ignore_ancestry != svn_tristate_false));
}