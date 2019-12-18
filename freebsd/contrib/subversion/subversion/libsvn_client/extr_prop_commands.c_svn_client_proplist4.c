#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_proplist_receiver2_t ;
struct TYPE_12__ {scalar_t__ kind; } ;
typedef  TYPE_1__ svn_opt_revision_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_depth_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
typedef  int svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 scalar_t__ SVN_CLIENT__REVKIND_IS_LOCAL_TO_WC (scalar_t__) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  get_local_props (char const*,TYPE_1__ const*,scalar_t__,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_remote_props (char const*,TYPE_1__ const*,TYPE_1__ const*,scalar_t__,int,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_cl__rev_default_to_head_or_working (TYPE_1__ const*,char const*) ; 
 TYPE_1__* svn_cl__rev_default_to_peg (TYPE_1__ const*,TYPE_1__ const*) ; 
 scalar_t__ svn_depth_empty ; 
 scalar_t__ svn_depth_unknown ; 
 scalar_t__ svn_opt_revision_unspecified ; 
 scalar_t__ svn_opt_revision_working ; 
 int /*<<< orphan*/  svn_path_is_url (char const*) ; 

svn_error_t *
svn_client_proplist4(const char *path_or_url,
                     const svn_opt_revision_t *peg_revision,
                     const svn_opt_revision_t *revision,
                     svn_depth_t depth,
                     const apr_array_header_t *changelists,
                     svn_boolean_t get_target_inherited_props,
                     svn_proplist_receiver2_t receiver,
                     void *receiver_baton,
                     svn_client_ctx_t *ctx,
                     apr_pool_t *scratch_pool)
{
  svn_boolean_t local_explicit_props;
  svn_boolean_t local_iprops;

  peg_revision = svn_cl__rev_default_to_head_or_working(peg_revision,
                                                        path_or_url);
  revision = svn_cl__rev_default_to_peg(revision, peg_revision);

  if (depth == svn_depth_unknown)
    depth = svn_depth_empty;

  /* Are explicit props available locally? */
  local_explicit_props =
    (! svn_path_is_url(path_or_url)
     && SVN_CLIENT__REVKIND_IS_LOCAL_TO_WC(peg_revision->kind)
     && SVN_CLIENT__REVKIND_IS_LOCAL_TO_WC(revision->kind));

  /* If we want iprops are they available locally? */
  local_iprops =
    (get_target_inherited_props /* We want iprops */
     && local_explicit_props /* No local explicit props means no local iprops. */
     && (peg_revision->kind == svn_opt_revision_working
         || peg_revision->kind == svn_opt_revision_unspecified )
     && (revision->kind == svn_opt_revision_working
         || revision->kind == svn_opt_revision_unspecified ));

  if ((get_target_inherited_props && !local_iprops)
      || !local_explicit_props)
    {
      SVN_ERR(get_remote_props(path_or_url, peg_revision, revision, depth,
                               !local_explicit_props,
                               (get_target_inherited_props && !local_iprops),
                               receiver, receiver_baton, ctx, scratch_pool));
    }

  if (local_explicit_props)
    {
      SVN_ERR(get_local_props(path_or_url, revision, depth, changelists,
                              local_iprops, receiver, receiver_baton, ctx,
                              scratch_pool));
    }

  return SVN_NO_ERROR;
}