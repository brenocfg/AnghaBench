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
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_9__ {TYPE_2__* repository; } ;
typedef  TYPE_3__ server_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_8__ {int /*<<< orphan*/  fs; TYPE_1__* fs_path; } ;
struct TYPE_7__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_CMD_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_DEPTH_INFINITY_OR_FILES (scalar_t__) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  accept_report (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  log_command (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  must_have_access (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_authz_read ; 
 int /*<<< orphan*/  svn_depth_from_word (char const*) ; 
 int /*<<< orphan*/  svn_depth_unknown ; 
 int /*<<< orphan*/  svn_fs_youngest_rev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* svn_fspath__join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_log__checkout (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_log__update (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_svn__parse_tuple (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char const**,scalar_t__*,char const**,scalar_t__*,scalar_t__*) ; 
 char* svn_relpath_canonicalize (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_tristate_true ; 

__attribute__((used)) static svn_error_t *
update(svn_ra_svn_conn_t *conn,
       apr_pool_t *pool,
       svn_ra_svn__list_t *params,
       void *baton)
{
  server_baton_t *b = baton;
  svn_revnum_t rev;
  const char *target, *full_path, *depth_word;
  svn_boolean_t recurse;
  svn_tristate_t send_copyfrom_args; /* Optional; default FALSE */
  svn_tristate_t ignore_ancestry; /* Optional; default FALSE */
  /* Default to unknown.  Old clients won't send depth, but we'll
     handle that by converting recurse if necessary. */
  svn_depth_t depth = svn_depth_unknown;
  svn_boolean_t is_checkout;

  /* Parse the arguments. */
  SVN_ERR(svn_ra_svn__parse_tuple(params, "(?r)cb?w3?3", &rev, &target,
                                  &recurse, &depth_word,
                                  &send_copyfrom_args, &ignore_ancestry));
  target = svn_relpath_canonicalize(target, pool);

  if (depth_word)
    depth = svn_depth_from_word(depth_word);
  else
    depth = SVN_DEPTH_INFINITY_OR_FILES(recurse);

  full_path = svn_fspath__join(b->repository->fs_path->data, target, pool);
  /* Check authorization and authenticate the user if necessary. */
  SVN_ERR(must_have_access(conn, pool, b, svn_authz_read, full_path, FALSE));

  if (!SVN_IS_VALID_REVNUM(rev))
    SVN_CMD_ERR(svn_fs_youngest_rev(&rev, b->repository->fs, pool));

  SVN_ERR(accept_report(&is_checkout, NULL,
                        conn, pool, b, rev, target, NULL, TRUE,
                        depth,
                        (send_copyfrom_args == svn_tristate_true),
                        (ignore_ancestry == svn_tristate_true)));
  if (is_checkout)
    {
      SVN_ERR(log_command(b, conn, pool, "%s",
                          svn_log__checkout(full_path, rev,
                                            depth, pool)));
    }
  else
    {
      SVN_ERR(log_command(b, conn, pool, "%s",
                          svn_log__update(full_path, rev, depth,
                                          (send_copyfrom_args
                                           == svn_tristate_true),
                                          pool)));
    }

  return SVN_NO_ERROR;
}