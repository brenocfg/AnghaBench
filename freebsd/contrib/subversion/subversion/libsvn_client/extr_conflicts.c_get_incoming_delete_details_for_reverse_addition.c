#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_session_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
struct find_added_rev_baton {char const* victim_abspath; int /*<<< orphan*/ * repos_relpath; void* added_rev; int /*<<< orphan*/ * pool; int /*<<< orphan*/ * parent_repos_relpath; int /*<<< orphan*/ * ctx; int /*<<< orphan*/  member_0; } ;
struct conflict_tree_incoming_delete_details {scalar_t__ replacing_node_kind; void* added_rev; void* rev_author; void* repos_relpath; void* deleted_rev; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 void* SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_REVISION_AUTHOR ; 
 void* _ (char*) ; 
 struct conflict_tree_incoming_delete_details* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 void* apr_pstrdup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  find_added_rev ; 
 void* rev_below (void*) ; 
 int /*<<< orphan*/  svn_client__open_ra_session_internal (int /*<<< orphan*/ **,char const**,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_none ; 
 char* svn_path_url_add_component2 (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_check_path (int /*<<< orphan*/ *,char*,void*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_get_location_segments (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct find_added_rev_baton*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_rev_prop (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,TYPE_1__**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_incoming_delete_details_for_reverse_addition(
  struct conflict_tree_incoming_delete_details **details,
  const char *repos_root_url,
  const char *old_repos_relpath,
  svn_revnum_t old_rev,
  svn_revnum_t new_rev,
  svn_client_ctx_t *ctx,
  const char *victim_abspath,
  apr_pool_t *result_pool,
  apr_pool_t *scratch_pool)
{
  svn_ra_session_t *ra_session;
  const char *url;
  const char *corrected_url;
  svn_string_t *author_revprop;
  struct find_added_rev_baton b = { 0 };

  url = svn_path_url_add_component2(repos_root_url, old_repos_relpath,
                                    scratch_pool);
  SVN_ERR(svn_client__open_ra_session_internal(&ra_session,
                                               &corrected_url,
                                               url, NULL, NULL,
                                               FALSE,
                                               FALSE,
                                               ctx,
                                               scratch_pool,
                                               scratch_pool));

  *details = apr_pcalloc(result_pool, sizeof(**details));
  b.ctx = ctx;
  b.victim_abspath = victim_abspath;
  b.added_rev = SVN_INVALID_REVNUM;
  b.repos_relpath = NULL;
  b.parent_repos_relpath = NULL;
  b.pool = scratch_pool;

  /* Figure out when this node was added. */
  SVN_ERR(svn_ra_get_location_segments(ra_session, "", old_rev,
                                       old_rev, new_rev,
                                       find_added_rev, &b,
                                       scratch_pool));

  SVN_ERR(svn_ra_rev_prop(ra_session, b.added_rev,
                          SVN_PROP_REVISION_AUTHOR,
                          &author_revprop, scratch_pool));
  (*details)->deleted_rev = SVN_INVALID_REVNUM;
  (*details)->added_rev = b.added_rev;
  (*details)->repos_relpath = apr_pstrdup(result_pool, b.repos_relpath);
  if (author_revprop)
    (*details)->rev_author = apr_pstrdup(result_pool, author_revprop->data);
  else
    (*details)->rev_author = _("unknown author");

  /* Check for replacement. */
  (*details)->replacing_node_kind = svn_node_none;
  if ((*details)->added_rev > 0)
    {
      svn_node_kind_t replaced_node_kind;

      SVN_ERR(svn_ra_check_path(ra_session, "",
                                rev_below((*details)->added_rev),
                                &replaced_node_kind, scratch_pool));
      if (replaced_node_kind != svn_node_none)
        SVN_ERR(svn_ra_check_path(ra_session, "", (*details)->added_rev,
                                  &(*details)->replacing_node_kind,
                                  scratch_pool));
    }

  return SVN_NO_ERROR;
}