#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_5__ ;
typedef  struct TYPE_32__   TYPE_4__ ;
typedef  struct TYPE_31__   TYPE_3__ ;
typedef  struct TYPE_30__   TYPE_2__ ;
typedef  struct TYPE_29__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_session_t ;
struct TYPE_29__ {int /*<<< orphan*/  number; } ;
struct TYPE_30__ {scalar_t__ member_0; scalar_t__ kind; TYPE_1__ value; } ;
typedef  TYPE_2__ svn_opt_revision_t ;
typedef  scalar_t__ svn_node_kind_t ;
struct TYPE_31__ {scalar_t__ apr_err; } ;
typedef  TYPE_3__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
struct TYPE_32__ {int /*<<< orphan*/  wc_ctx; } ;
typedef  TYPE_4__ svn_client_ctx_t ;
struct TYPE_33__ {int /*<<< orphan*/  url; int /*<<< orphan*/  rev; } ;
typedef  TYPE_5__ svn_client__pathrev_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_CLIENT_BAD_REVISION ; 
 scalar_t__ SVN_ERR_RA_ILLEGAL_URL ; 
 scalar_t__ SVN_ERR_UNSUPPORTED_FEATURE ; 
 scalar_t__ SVN_ERR_WC_NODE_KIND_CHANGE ; 
 scalar_t__ SVN_ERR_WC_OBSTRUCTED_UPDATE ; 
 TYPE_3__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  initialize_area (char const*,TYPE_5__*,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_client__ra_session_from_path2 (int /*<<< orphan*/ **,TYPE_5__**,char const*,int /*<<< orphan*/ *,TYPE_2__ const*,TYPE_2__ const*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client__resolve_rev_and_url (TYPE_5__**,int /*<<< orphan*/ *,char const*,TYPE_2__ const*,TYPE_2__ const*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client__update_internal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_is_absolute (char const*) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_3__*) ; 
 TYPE_3__* svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_error_createf (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* svn_error_trace (TYPE_3__*) ; 
 int /*<<< orphan*/  svn_io_check_path (char const*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_make_dir_recursively (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_file ; 
 scalar_t__ svn_node_none ; 
 scalar_t__ svn_opt_revision_date ; 
 scalar_t__ svn_opt_revision_head ; 
 scalar_t__ svn_opt_revision_number ; 
 int /*<<< orphan*/  svn_ra_check_path (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_ra_reparent (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_uri_is_canonical (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__node_get_url (char const**,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_check_wc2 (int*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_client__checkout_internal(svn_revnum_t *result_rev,
                              svn_boolean_t *timestamp_sleep,
                              const char *url,
                              const char *local_abspath,
                              const svn_opt_revision_t *peg_revision,
                              const svn_opt_revision_t *revision,
                              svn_depth_t depth,
                              svn_boolean_t ignore_externals,
                              svn_boolean_t allow_unver_obstructions,
                              svn_ra_session_t *ra_session,
                              svn_client_ctx_t *ctx,
                              apr_pool_t *scratch_pool)
{
  svn_node_kind_t kind;
  svn_client__pathrev_t *pathrev;
  svn_opt_revision_t resolved_rev = { svn_opt_revision_number };

  /* Sanity check.  Without these, the checkout is meaningless. */
  SVN_ERR_ASSERT(local_abspath != NULL);
  SVN_ERR_ASSERT(svn_uri_is_canonical(url, scratch_pool));
  SVN_ERR_ASSERT(svn_dirent_is_absolute(local_abspath));

  /* Fulfill the docstring promise of svn_client_checkout: */
  if ((revision->kind != svn_opt_revision_number)
      && (revision->kind != svn_opt_revision_date)
      && (revision->kind != svn_opt_revision_head))
    return svn_error_create(SVN_ERR_CLIENT_BAD_REVISION, NULL, NULL);

  /* Get the RA connection, if needed. */
  if (ra_session)
    {
      svn_error_t *err = svn_ra_reparent(ra_session, url, scratch_pool);

      if (err)
        {
          if (err->apr_err == SVN_ERR_RA_ILLEGAL_URL)
            {
              svn_error_clear(err);
              ra_session = NULL;
            }
          else
            return svn_error_trace(err);
        }
      else
        {
          SVN_ERR(svn_client__resolve_rev_and_url(&pathrev,
                                                  ra_session, url,
                                                  peg_revision, revision,
                                                  ctx, scratch_pool));
        }
    }

  if (!ra_session)
    {
      SVN_ERR(svn_client__ra_session_from_path2(&ra_session, &pathrev,
                                                url, NULL, peg_revision,
                                                revision, ctx, scratch_pool));
    }

  SVN_ERR(svn_ra_check_path(ra_session, "", pathrev->rev, &kind, scratch_pool));
  resolved_rev.value.number = pathrev->rev;

  if (kind == svn_node_none)
    return svn_error_createf(SVN_ERR_RA_ILLEGAL_URL, NULL,
                             _("URL '%s' doesn't exist"), pathrev->url);
  else if (kind == svn_node_file)
    return svn_error_createf
      (SVN_ERR_UNSUPPORTED_FEATURE , NULL,
       _("URL '%s' refers to a file, not a directory"), pathrev->url);

  SVN_ERR(svn_io_check_path(local_abspath, &kind, scratch_pool));

  if (kind == svn_node_none)
    {
      /* Bootstrap: create an incomplete working-copy root dir.  Its
         entries file should only have an entry for THIS_DIR with a
         URL, revnum, and an 'incomplete' flag.  */
      SVN_ERR(svn_io_make_dir_recursively(local_abspath, scratch_pool));
      SVN_ERR(initialize_area(local_abspath, pathrev, depth, ctx,
                              scratch_pool));
    }
  else if (kind == svn_node_dir)
    {
      int wc_format;
      const char *entry_url;

      SVN_ERR(svn_wc_check_wc2(&wc_format, ctx->wc_ctx, local_abspath,
                               scratch_pool));

      if (! wc_format)
        {
          SVN_ERR(initialize_area(local_abspath, pathrev, depth, ctx,
                                  scratch_pool));
        }
      else
        {
          /* Get PATH's URL. */
          SVN_ERR(svn_wc__node_get_url(&entry_url, ctx->wc_ctx, local_abspath,
                                       scratch_pool, scratch_pool));

          /* If PATH's existing URL matches the incoming one, then
             just update.  This allows 'svn co' to restart an
             interrupted checkout.  Otherwise bail out. */
          if (strcmp(entry_url, pathrev->url) != 0)
            return svn_error_createf(
                          SVN_ERR_WC_OBSTRUCTED_UPDATE, NULL,
                          _("'%s' is already a working copy for a"
                            " different URL"),
                          svn_dirent_local_style(local_abspath, scratch_pool));
        }
    }
  else
    {
      return svn_error_createf(SVN_ERR_WC_NODE_KIND_CHANGE, NULL,
                               _("'%s' already exists and is not a directory"),
                               svn_dirent_local_style(local_abspath,
                                                      scratch_pool));
    }

  /* Have update fix the incompleteness. */
  SVN_ERR(svn_client__update_internal(result_rev, timestamp_sleep,
                                      local_abspath, &resolved_rev, depth,
                                      TRUE, ignore_externals,
                                      allow_unver_obstructions,
                                      TRUE /* adds_as_modification */,
                                      FALSE, FALSE, ra_session,
                                      ctx, scratch_pool));

  return SVN_NO_ERROR;
}