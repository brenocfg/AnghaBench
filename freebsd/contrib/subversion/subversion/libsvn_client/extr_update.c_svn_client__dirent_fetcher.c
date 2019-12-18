#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct svn_client__dirent_fetcher_baton_t {int /*<<< orphan*/  ra_session; int /*<<< orphan*/  target_revision; int /*<<< orphan*/  anchor_url; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_DIRENT_KIND ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_client__ensure_ra_session_url (char const**,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 
 char* svn_path_url_add_component2 (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_check_path (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_get_dir2 (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_get_path_relative_to_session (int /*<<< orphan*/ ,char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_reparent (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_uri__is_ancestor (int /*<<< orphan*/ ,char const*) ; 

svn_error_t *
svn_client__dirent_fetcher(void *baton,
                           apr_hash_t **dirents,
                           const char *repos_root_url,
                           const char *repos_relpath,
                           apr_pool_t *result_pool,
                           apr_pool_t *scratch_pool)
{
  struct svn_client__dirent_fetcher_baton_t *dfb = baton;
  const char *old_url = NULL;
  const char *session_relpath;
  svn_node_kind_t kind;
  const char *url;

  url = svn_path_url_add_component2(repos_root_url, repos_relpath,
                                    scratch_pool);

  if (!svn_uri__is_ancestor(dfb->anchor_url, url))
    {
      SVN_ERR(svn_client__ensure_ra_session_url(&old_url, dfb->ra_session,
                                                url, scratch_pool));
      session_relpath = "";
    }
  else
    SVN_ERR(svn_ra_get_path_relative_to_session(dfb->ra_session,
                                                &session_relpath, url,
                                                scratch_pool));

  /* Is session_relpath still a directory? */
  SVN_ERR(svn_ra_check_path(dfb->ra_session, session_relpath,
                            dfb->target_revision, &kind, scratch_pool));

  if (kind == svn_node_dir)
    SVN_ERR(svn_ra_get_dir2(dfb->ra_session, dirents, NULL, NULL,
                            session_relpath, dfb->target_revision,
                            SVN_DIRENT_KIND, result_pool));
  else
    *dirents = NULL;

  if (old_url)
    SVN_ERR(svn_ra_reparent(dfb->ra_session, old_url, scratch_pool));

  return SVN_NO_ERROR;
}