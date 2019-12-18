#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_svn_conn_t ;
typedef  int /*<<< orphan*/  svn_ra_svn__list_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_2__ {int /*<<< orphan*/  only_empty_entries; int /*<<< orphan*/  entry_counter; int /*<<< orphan*/  report_baton; scalar_t__ err; int /*<<< orphan*/ * from_rev; } ;
typedef  TYPE_1__ report_driver_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  svn_depth_from_word (char const*) ; 
 int /*<<< orphan*/  svn_depth_infinity ; 
 int /*<<< orphan*/  svn_ra_svn__parse_tuple (int /*<<< orphan*/ *,char*,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,char const**) ; 
 char* svn_relpath_canonicalize (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_repos_set_path3 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *set_path(svn_ra_svn_conn_t *conn, apr_pool_t *pool,
                             svn_ra_svn__list_t *params, void *baton)
{
  report_driver_baton_t *b = baton;
  const char *path, *lock_token, *depth_word;
  svn_revnum_t rev;
  /* Default to infinity, for old clients that don't send depth. */
  svn_depth_t depth = svn_depth_infinity;
  svn_boolean_t start_empty;

  SVN_ERR(svn_ra_svn__parse_tuple(params, "crb?(?c)?w",
                                  &path, &rev, &start_empty, &lock_token,
                                  &depth_word));
  if (depth_word)
    depth = svn_depth_from_word(depth_word);
  path = svn_relpath_canonicalize(path, pool);
  if (b->from_rev && strcmp(path, "") == 0)
    *b->from_rev = rev;
  if (!b->err)
    b->err = svn_repos_set_path3(b->report_baton, path, rev, depth,
                                 start_empty, lock_token, pool);
  b->entry_counter++;
  if (!start_empty)
    b->only_empty_entries = FALSE;
  return SVN_NO_ERROR;
}