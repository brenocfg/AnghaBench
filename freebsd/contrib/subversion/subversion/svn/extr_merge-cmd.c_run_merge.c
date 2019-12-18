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
struct TYPE_11__ {scalar_t__ kind; } ;
typedef  TYPE_1__ svn_opt_revision_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
struct TYPE_12__ {int /*<<< orphan*/  allow_mixed_rev; int /*<<< orphan*/  dry_run; int /*<<< orphan*/  record_only; int /*<<< orphan*/  force; int /*<<< orphan*/  ignore_ancestry; int /*<<< orphan*/  depth; scalar_t__ verbose; scalar_t__ reintegrate; } ;
typedef  TYPE_2__ svn_cl__opt_state_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_CL_ARG_PARSING_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * svn_cl__deprecated_merge_reintegrate (char const*,TYPE_1__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_client_merge5 (char const*,TYPE_1__*,char const*,TYPE_1__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_client_merge_peg5 (char const*,int /*<<< orphan*/ *,TYPE_1__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cmdline_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ svn_opt_revision_unspecified ; 
 scalar_t__ svn_path_is_url (char const*) ; 

__attribute__((used)) static svn_error_t *
run_merge(svn_boolean_t two_sources_specified,
          const char *sourcepath1,
          svn_opt_revision_t peg_revision1,
          const char *sourcepath2,
          const char *targetpath,
          apr_array_header_t *ranges_to_merge,
          svn_opt_revision_t first_range_start,
          svn_opt_revision_t first_range_end,
          svn_cl__opt_state_t *opt_state,
          apr_array_header_t *options,
          svn_client_ctx_t *ctx,
          apr_pool_t *scratch_pool)
{
  svn_error_t *merge_err;

  if (opt_state->reintegrate)
    {
      merge_err = svn_cl__deprecated_merge_reintegrate(
                    sourcepath1, &peg_revision1, targetpath,
                    opt_state->dry_run, options, ctx, scratch_pool);
    }
  else if (! two_sources_specified)
    {
      /* If we don't have at least one valid revision range, pick a
         good one that spans the entire set of revisions on our
         source. */
      if ((first_range_start.kind == svn_opt_revision_unspecified)
          && (first_range_end.kind == svn_opt_revision_unspecified))
        {
          ranges_to_merge = NULL;
        }

      if (opt_state->verbose)
        SVN_ERR(svn_cmdline_printf(scratch_pool, _("--- Merging\n")));
      merge_err = svn_client_merge_peg5(sourcepath1,
                                        ranges_to_merge,
                                        &peg_revision1,
                                        targetpath,
                                        opt_state->depth,
                                        opt_state->ignore_ancestry,
                                        opt_state->ignore_ancestry,
                                        opt_state->force, /* force_delete */
                                        opt_state->record_only,
                                        opt_state->dry_run,
                                        opt_state->allow_mixed_rev,
                                        options,
                                        ctx,
                                        scratch_pool);
    }
  else
    {
      if (svn_path_is_url(sourcepath1) != svn_path_is_url(sourcepath2))
        return svn_error_create(SVN_ERR_CL_ARG_PARSING_ERROR, NULL,
                                _("Merge sources must both be "
                                  "either paths or URLs"));

      if (svn_path_is_url(targetpath))
        return svn_error_createf(SVN_ERR_CL_ARG_PARSING_ERROR, NULL,
                                 _("Merge target '%s' must be a local path "
                                   "but looks like a URL"), targetpath);

      if (opt_state->verbose)
        SVN_ERR(svn_cmdline_printf(scratch_pool, _("--- Merging\n")));
      merge_err = svn_client_merge5(sourcepath1,
                                    &first_range_start,
                                    sourcepath2,
                                    &first_range_end,
                                    targetpath,
                                    opt_state->depth,
                                    opt_state->ignore_ancestry,
                                    opt_state->ignore_ancestry,
                                    opt_state->force, /* force_delete */
                                    opt_state->record_only,
                                    opt_state->dry_run,
                                    opt_state->allow_mixed_rev,
                                    options,
                                    ctx,
                                    scratch_pool);
    }

  return merge_err;
}