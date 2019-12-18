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
struct TYPE_2__ {char const* repos_url; int /*<<< orphan*/  entry_counter; int /*<<< orphan*/  report_baton; scalar_t__ err; } ;
typedef  TYPE_1__ report_driver_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ get_fs_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  svn_depth_from_word (char const*) ; 
 int /*<<< orphan*/  svn_depth_infinity ; 
 int /*<<< orphan*/  svn_path_uri_decode (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_svn__parse_tuple (int /*<<< orphan*/ *,char*,char const**,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,char const**) ; 
 char* svn_relpath_canonicalize (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_repos_link_path3 (int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 char* svn_uri_canonicalize (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *link_path(svn_ra_svn_conn_t *conn, apr_pool_t *pool,
                              svn_ra_svn__list_t *params, void *baton)
{
  report_driver_baton_t *b = baton;
  const char *path, *url, *lock_token, *fs_path, *depth_word;
  svn_revnum_t rev;
  svn_boolean_t start_empty;
  /* Default to infinity, for old clients that don't send depth. */
  svn_depth_t depth = svn_depth_infinity;

  SVN_ERR(svn_ra_svn__parse_tuple(params, "ccrb?(?c)?w",
                                 &path, &url, &rev, &start_empty,
                                 &lock_token, &depth_word));

  /* ### WHAT?!  The link path is an absolute URL?!  Didn't see that
     coming...   -- cmpilato  */
  path = svn_relpath_canonicalize(path, pool);
  url = svn_uri_canonicalize(url, pool);
  if (depth_word)
    depth = svn_depth_from_word(depth_word);
  if (!b->err)
    b->err = get_fs_path(svn_path_uri_decode(b->repos_url, pool),
                         svn_path_uri_decode(url, pool),
                         &fs_path);
  if (!b->err)
    b->err = svn_repos_link_path3(b->report_baton, path, fs_path, rev,
                                  depth, start_empty, lock_token, pool);
  b->entry_counter++;
  return SVN_NO_ERROR;
}