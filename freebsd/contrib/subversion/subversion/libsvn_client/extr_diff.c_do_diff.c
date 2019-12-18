#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ kind; } ;
typedef  TYPE_1__ svn_opt_revision_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_diff_tree_processor_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  diff_driver_info_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  check_paths (scalar_t__*,scalar_t__*,char const*,char const*,TYPE_1__ const*,TYPE_1__ const*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  diff_repos_repos (char const**,scalar_t__*,int /*<<< orphan*/ *,char const*,char const*,TYPE_1__ const*,TYPE_1__ const*,TYPE_1__ const*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  diff_repos_wc (char const**,scalar_t__*,int /*<<< orphan*/ *,char const*,TYPE_1__ const*,TYPE_1__ const*,char const*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  diff_wc_wc (char const**,scalar_t__*,int /*<<< orphan*/ *,char const*,TYPE_1__ const*,char const*,TYPE_1__ const*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client__arbitrary_nodes_diff (char const**,scalar_t__*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_get_absolute (char const**,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_opt_revision_working ; 

__attribute__((used)) static svn_error_t *
do_diff(const char **root_relpath,
        svn_boolean_t *root_is_dir,
        diff_driver_info_t *ddi,
        const char *path_or_url1,
        const char *path_or_url2,
        const svn_opt_revision_t *revision1,
        const svn_opt_revision_t *revision2,
        const svn_opt_revision_t *peg_revision,
        svn_boolean_t no_peg_revision,
        svn_depth_t depth,
        svn_boolean_t ignore_ancestry,
        const apr_array_header_t *changelists,
        svn_boolean_t text_deltas,
        const svn_diff_tree_processor_t *diff_processor,
        svn_client_ctx_t *ctx,
        apr_pool_t *result_pool,
        apr_pool_t *scratch_pool)
{
  svn_boolean_t is_repos1;
  svn_boolean_t is_repos2;

  /* Check if paths/revisions are urls/local. */
  SVN_ERR(check_paths(&is_repos1, &is_repos2, path_or_url1, path_or_url2,
                      revision1, revision2, peg_revision));

  if (is_repos1)
    {
      if (is_repos2)
        {
          /* Ignores changelists. */
          SVN_ERR(diff_repos_repos(root_relpath, root_is_dir,
                                   ddi,
                                   path_or_url1, path_or_url2,
                                   revision1, revision2,
                                   peg_revision, depth, ignore_ancestry,
                                   text_deltas,
                                   diff_processor, ctx,
                                   result_pool, scratch_pool));
        }
      else /* path_or_url2 is a working copy path */
        {
          SVN_ERR(diff_repos_wc(root_relpath, root_is_dir, ddi,
                                path_or_url1, revision1,
                                no_peg_revision ? revision1
                                                : peg_revision,
                                path_or_url2, revision2->kind,
                                FALSE, depth,
                                ignore_ancestry, changelists,
                                diff_processor, ctx,
                                result_pool, scratch_pool));
        }
    }
  else /* path_or_url1 is a working copy path */
    {
      if (is_repos2)
        {
          SVN_ERR(diff_repos_wc(root_relpath, root_is_dir, ddi,
                                path_or_url2, revision2,
                                no_peg_revision ? revision2
                                                : peg_revision,
                                path_or_url1,
                                revision1->kind,
                                TRUE, depth,
                                ignore_ancestry, changelists,
                                diff_processor, ctx,
                                result_pool, scratch_pool));
        }
      else /* path_or_url2 is a working copy path */
        {
          if (revision1->kind == svn_opt_revision_working
              && revision2->kind == svn_opt_revision_working)
            {
              const char *abspath1;
              const char *abspath2;

              SVN_ERR(svn_dirent_get_absolute(&abspath1, path_or_url1,
                                              scratch_pool));
              SVN_ERR(svn_dirent_get_absolute(&abspath2, path_or_url2,
                                              scratch_pool));

              /* ### What about ddi? */
              /* Ignores changelists, ignore_ancestry */
              SVN_ERR(svn_client__arbitrary_nodes_diff(root_relpath, root_is_dir,
                                                       abspath1, abspath2,
                                                       depth,
                                                       diff_processor,
                                                       ctx,
                                                       result_pool, scratch_pool));
            }
          else
            {
              SVN_ERR(diff_wc_wc(root_relpath, root_is_dir, ddi,
                                 path_or_url1, revision1,
                                 path_or_url2, revision2,
                                 depth, ignore_ancestry, changelists,
                                 diff_processor, ctx,
                                 result_pool, scratch_pool));
            }
        }
    }

  return SVN_NO_ERROR;
}