#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_session_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
struct TYPE_5__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ svn_client_conflict_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  find_revision_for_suspected_deletion (scalar_t__*,char const**,scalar_t__*,int /*<<< orphan*/ **,TYPE_1__*,char const*,char const*,scalar_t__,int /*<<< orphan*/ ,char const*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ rev_below (scalar_t__) ; 
 int /*<<< orphan*/  svn_client__open_ra_session_internal (int /*<<< orphan*/ **,char const**,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client_conflict_get_repos_info (char const**,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_none ; 
 char* svn_path_url_add_component2 (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_check_path (int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__*,int /*<<< orphan*/ *) ; 
 char* svn_relpath_basename (char const*,int /*<<< orphan*/ *) ; 
 char* svn_relpath_dirname (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
find_related_node(const char **related_repos_relpath,
                  svn_revnum_t *related_peg_rev,
                  const char *younger_related_repos_relpath,
                  svn_revnum_t younger_related_peg_rev,
                  const char *older_repos_relpath,
                  svn_revnum_t older_peg_rev,
                  svn_client_conflict_t *conflict,
                  svn_client_ctx_t *ctx,
                  apr_pool_t *result_pool,
                  apr_pool_t *scratch_pool)
{
  const char *repos_root_url;
  const char *related_url;
  const char *corrected_url;
  svn_node_kind_t related_node_kind;
  svn_ra_session_t *ra_session;

  *related_repos_relpath = NULL;
  *related_peg_rev = SVN_INVALID_REVNUM;

  SVN_ERR(svn_client_conflict_get_repos_info(&repos_root_url, NULL,
                                             conflict,
                                             scratch_pool, scratch_pool));
  related_url = svn_path_url_add_component2(repos_root_url,
                                            younger_related_repos_relpath,
                                            scratch_pool);
  SVN_ERR(svn_client__open_ra_session_internal(&ra_session,
                                               &corrected_url,
                                               related_url, NULL,
                                               NULL,
                                               FALSE,
                                               FALSE,
                                               ctx,
                                               scratch_pool,
                                               scratch_pool));
  SVN_ERR(svn_ra_check_path(ra_session, "", younger_related_peg_rev,
                            &related_node_kind, scratch_pool));
  if (related_node_kind == svn_node_none)
    {
      svn_revnum_t related_deleted_rev;
      const char *related_deleted_rev_author;
      svn_node_kind_t related_replacing_node_kind;
      const char *related_basename;
      const char *related_parent_repos_relpath;
      apr_array_header_t *related_moves;

      /* Looks like the younger node, which we'd like to use as our
       * 'related node', was deleted. Try to find its deleted revision
       *  so we can calculate a peg revision at which it exists.
       * The younger node is related to the older node, so we can use
       * the older node to guide us in our search. */
      related_basename = svn_relpath_basename(younger_related_repos_relpath,
                                              scratch_pool);
      related_parent_repos_relpath =
        svn_relpath_dirname(younger_related_repos_relpath, scratch_pool);
      SVN_ERR(find_revision_for_suspected_deletion(
                &related_deleted_rev, &related_deleted_rev_author,
                &related_replacing_node_kind, &related_moves,
                conflict, related_basename,
                related_parent_repos_relpath,
                younger_related_peg_rev, 0,
                older_repos_relpath, older_peg_rev,
                ctx, conflict->pool, scratch_pool));

      /* If we can't find a related node, bail. */
      if (related_deleted_rev == SVN_INVALID_REVNUM)
        return SVN_NO_ERROR;

      /* The node should exist in the revision before it was deleted. */
      *related_repos_relpath = younger_related_repos_relpath;
      *related_peg_rev = rev_below(related_deleted_rev);
    }
  else
    {
      *related_repos_relpath = younger_related_repos_relpath;
      *related_peg_rev = younger_related_peg_rev;
    }

  return SVN_NO_ERROR;
}