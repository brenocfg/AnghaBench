#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_wc_operation_t ;
struct TYPE_11__ {char const* data; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
struct TYPE_12__ {struct conflict_tree_incoming_add_details* tree_conflict_incoming_details; int /*<<< orphan*/  pool; } ;
typedef  TYPE_2__ svn_client_conflict_t ;
struct find_added_rev_baton {scalar_t__ added_rev; char const* repos_relpath; int /*<<< orphan*/ * pool; int /*<<< orphan*/ * parent_repos_relpath; int /*<<< orphan*/ * ctx; void* victim_abspath; int /*<<< orphan*/  member_0; } ;
struct conflict_tree_incoming_add_details {scalar_t__ added_rev; int /*<<< orphan*/ * moves; int /*<<< orphan*/ * added_rev_author; int /*<<< orphan*/ * deleted_rev_author; scalar_t__ deleted_rev; void* repos_relpath; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_INVALID_REVNUM ; 
 scalar_t__ SVN_IS_VALID_REVNUM (scalar_t__) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_REVISION_AUTHOR ; 
 void* _ (char*) ; 
 struct conflict_tree_incoming_add_details* apr_pcalloc (int /*<<< orphan*/ ,int) ; 
 void* apr_pstrdup (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  find_added_rev ; 
 int /*<<< orphan*/  find_revision_for_suspected_deletion (scalar_t__*,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ **,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client__open_ra_session_internal (int /*<<< orphan*/ **,char const**,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client_conflict_get_incoming_new_repos_location (char const**,scalar_t__*,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client_conflict_get_incoming_old_repos_location (char const**,scalar_t__*,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* svn_client_conflict_get_local_abspath (TYPE_2__*) ; 
 scalar_t__ svn_client_conflict_get_operation (TYPE_2__*) ; 
 int /*<<< orphan*/  svn_client_conflict_get_repos_info (char const**,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* svn_path_url_add_component2 (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_get_deleted_rev (int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_get_latest_revnum (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_get_location_segments (int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,struct find_added_rev_baton*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_rev_prop (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,TYPE_1__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_relpath_basename (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_relpath_dirname (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc_operation_merge ; 
 scalar_t__ svn_wc_operation_switch ; 
 scalar_t__ svn_wc_operation_update ; 

__attribute__((used)) static svn_error_t *
conflict_tree_get_details_incoming_add(svn_client_conflict_t *conflict,
                                       svn_client_ctx_t *ctx,
                                       apr_pool_t *scratch_pool)
{
  const char *old_repos_relpath;
  const char *new_repos_relpath;
  const char *repos_root_url;
  svn_revnum_t old_rev;
  svn_revnum_t new_rev;
  struct conflict_tree_incoming_add_details *details;
  svn_wc_operation_t operation;

  SVN_ERR(svn_client_conflict_get_incoming_old_repos_location(
            &old_repos_relpath, &old_rev, NULL, conflict, scratch_pool,
            scratch_pool));
  SVN_ERR(svn_client_conflict_get_incoming_new_repos_location(
            &new_repos_relpath, &new_rev, NULL, conflict, scratch_pool,
            scratch_pool));
  SVN_ERR(svn_client_conflict_get_repos_info(&repos_root_url, NULL,
                                             conflict,
                                             scratch_pool, scratch_pool));
  operation = svn_client_conflict_get_operation(conflict);

  if (operation == svn_wc_operation_update ||
      operation == svn_wc_operation_switch)
    {
      /* Only the new repository location is recorded for the node which
       * caused an incoming addition. There is no pre-update/pre-switch
       * revision to be recorded for the node since it does not exist in
       * the repository at that revision.
       * The implication is that we cannot know whether the operation went
       * forward or backwards in history. So always try to find an added
       * and a deleted revision for the node. Users must figure out by whether
       * the addition or deletion caused the conflict. */
      const char *url;
      const char *corrected_url;
      svn_string_t *author_revprop;
      struct find_added_rev_baton b = { 0 };
      svn_ra_session_t *ra_session;
      svn_revnum_t deleted_rev;
      svn_revnum_t head_rev;

      url = svn_path_url_add_component2(repos_root_url, new_repos_relpath,
                                        scratch_pool);
      SVN_ERR(svn_client__open_ra_session_internal(&ra_session,
                                                   &corrected_url,
                                                   url, NULL, NULL,
                                                   FALSE,
                                                   FALSE,
                                                   ctx,
                                                   scratch_pool,
                                                   scratch_pool));

      details = apr_pcalloc(conflict->pool, sizeof(*details));
      b.ctx = ctx,
      b.victim_abspath = svn_client_conflict_get_local_abspath(conflict),
      b.added_rev = SVN_INVALID_REVNUM;
      b.repos_relpath = NULL;
      b.parent_repos_relpath = NULL;
      b.pool = scratch_pool;

      /* Figure out when this node was added. */
      SVN_ERR(svn_ra_get_location_segments(ra_session, "", new_rev,
                                           new_rev, SVN_INVALID_REVNUM,
                                           find_added_rev, &b,
                                           scratch_pool));

      SVN_ERR(svn_ra_rev_prop(ra_session, b.added_rev,
                              SVN_PROP_REVISION_AUTHOR,
                              &author_revprop, scratch_pool));
      details->repos_relpath = apr_pstrdup(conflict->pool, b.repos_relpath);
      details->added_rev = b.added_rev;
      if (author_revprop)
        details->added_rev_author = apr_pstrdup(conflict->pool,
                                          author_revprop->data);
      else
        details->added_rev_author = _("unknown author");
      details->deleted_rev = SVN_INVALID_REVNUM;
      details->deleted_rev_author = NULL;

      /* Figure out whether this node was deleted later.
       * ### Could probably optimize by infering both addition and deletion
       * ### from svn_ra_get_location_segments() call above. */
      SVN_ERR(svn_ra_get_latest_revnum(ra_session, &head_rev, scratch_pool));
      if (new_rev < head_rev)
        {
          SVN_ERR(svn_ra_get_deleted_rev(ra_session, "", new_rev, head_rev,
                                         &deleted_rev, scratch_pool));
          if (SVN_IS_VALID_REVNUM(deleted_rev))
           {
              SVN_ERR(svn_ra_rev_prop(ra_session, deleted_rev,
                                      SVN_PROP_REVISION_AUTHOR,
                                      &author_revprop, scratch_pool));
              details->deleted_rev = deleted_rev;
              if (author_revprop)
                details->deleted_rev_author = apr_pstrdup(conflict->pool,
                                                          author_revprop->data);
              else
                details->deleted_rev_author = _("unknown author");
            }
        }
    }
  else if (operation == svn_wc_operation_merge)
    {
      if (old_rev < new_rev)
        {
          /* The merge operation went forwards in history.
           * The addition of the node happened on the branch we merged form.
           * Scan the nodes's history to find the revision which added it. */
          const char *url;
          const char *corrected_url;
          svn_string_t *author_revprop;
          struct find_added_rev_baton b = { 0 };
          svn_ra_session_t *ra_session;

          url = svn_path_url_add_component2(repos_root_url, new_repos_relpath,
                                            scratch_pool);
          SVN_ERR(svn_client__open_ra_session_internal(&ra_session,
                                                       &corrected_url,
                                                       url, NULL, NULL,
                                                       FALSE,
                                                       FALSE,
                                                       ctx,
                                                       scratch_pool,
                                                       scratch_pool));

          details = apr_pcalloc(conflict->pool, sizeof(*details));
          b.victim_abspath = svn_client_conflict_get_local_abspath(conflict);
          b.ctx = ctx;
          b.added_rev = SVN_INVALID_REVNUM;
          b.repos_relpath = NULL;
          b.parent_repos_relpath = NULL;
          b.pool = scratch_pool;

          /* Figure out when this node was added. */
          SVN_ERR(svn_ra_get_location_segments(ra_session, "", new_rev,
                                               new_rev, old_rev,
                                               find_added_rev, &b,
                                               scratch_pool));

          SVN_ERR(svn_ra_rev_prop(ra_session, b.added_rev,
                                  SVN_PROP_REVISION_AUTHOR,
                                  &author_revprop, scratch_pool));
          details->repos_relpath = apr_pstrdup(conflict->pool, b.repos_relpath);
          details->added_rev = b.added_rev;
          if (author_revprop)
            details->added_rev_author = apr_pstrdup(conflict->pool,
                                                    author_revprop->data);
          else
            details->added_rev_author = _("unknown author");
          details->deleted_rev = SVN_INVALID_REVNUM;
          details->deleted_rev_author = NULL;
        }
      else
        {
          /* The merge operation was a reverse-merge.
           * This addition is in fact a deletion, applied in reverse,
           * which happened on the branch we merged from.
           * Find the revision which deleted the node. */
          svn_revnum_t deleted_rev;
          const char *deleted_rev_author;
          svn_node_kind_t replacing_node_kind;
          apr_array_header_t *moves;

          SVN_ERR(find_revision_for_suspected_deletion(
                    &deleted_rev, &deleted_rev_author, &replacing_node_kind,
                    &moves, conflict,
                    svn_relpath_basename(old_repos_relpath, scratch_pool),
                    svn_relpath_dirname(old_repos_relpath, scratch_pool),
                    old_rev, new_rev,
                    NULL, SVN_INVALID_REVNUM, /* related to self */
                    ctx,
                    conflict->pool, scratch_pool));
          if (deleted_rev == SVN_INVALID_REVNUM)
            {
              /* We could not determine the revision in which the node was
               * deleted. We cannot provide the required details so the best
               * we can do is fall back to the default description. */
              return SVN_NO_ERROR;
            }

          details = apr_pcalloc(conflict->pool, sizeof(*details));
          details->repos_relpath = apr_pstrdup(conflict->pool,
                                               new_repos_relpath);
          details->deleted_rev = deleted_rev;
          details->deleted_rev_author = apr_pstrdup(conflict->pool,
                                                    deleted_rev_author);

          details->added_rev = SVN_INVALID_REVNUM;
          details->added_rev_author = NULL;
          details->moves = moves;
        }
    }
  else
    {
      details = NULL;
    }

  conflict->tree_conflict_incoming_details = details;

  return SVN_NO_ERROR;
}