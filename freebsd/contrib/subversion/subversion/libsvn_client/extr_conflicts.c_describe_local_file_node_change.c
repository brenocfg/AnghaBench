#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc_operation_t ;
typedef  int svn_wc_conflict_reason_t ;
struct TYPE_14__ {int /*<<< orphan*/  apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
struct TYPE_15__ {int /*<<< orphan*/  wc_ctx; } ;
typedef  TYPE_2__ svn_client_ctx_t ;
struct TYPE_16__ {int /*<<< orphan*/  local_abspath; } ;
typedef  TYPE_3__ svn_client_conflict_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_WC_PATH_NOT_FOUND ; 
 TYPE_1__* SVN_NO_ERROR ; 
 char* _ (char*) ; 
 char* apr_psprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int svn_client_conflict_get_local_change (TYPE_3__*) ; 
 int /*<<< orphan*/  svn_client_conflict_get_operation (TYPE_3__*) ; 
 int /*<<< orphan*/  svn_dirent_local_style (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_skip_ancestor (char const*,char const*) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 TYPE_1__* svn_error_trace (TYPE_1__*) ; 
 int /*<<< orphan*/  svn_wc__get_wcroot (char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_wc__node_was_moved_away (char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__node_was_moved_here (char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
#define  svn_wc_conflict_reason_added 136 
#define  svn_wc_conflict_reason_deleted 135 
#define  svn_wc_conflict_reason_edited 134 
#define  svn_wc_conflict_reason_missing 133 
#define  svn_wc_conflict_reason_moved_away 132 
#define  svn_wc_conflict_reason_moved_here 131 
#define  svn_wc_conflict_reason_obstructed 130 
#define  svn_wc_conflict_reason_replaced 129 
#define  svn_wc_conflict_reason_unversioned 128 
 int /*<<< orphan*/  svn_wc_operation_merge ; 
 int /*<<< orphan*/  svn_wc_operation_switch ; 
 int /*<<< orphan*/  svn_wc_operation_update ; 

__attribute__((used)) static svn_error_t *
describe_local_file_node_change(const char **description,
                                svn_client_conflict_t *conflict,
                                svn_client_ctx_t *ctx,
                                apr_pool_t *result_pool,
                                apr_pool_t *scratch_pool)
{
  svn_wc_conflict_reason_t local_change;
  svn_wc_operation_t operation;

  local_change = svn_client_conflict_get_local_change(conflict);
  operation = svn_client_conflict_get_operation(conflict);

  switch (local_change)
    {
      case svn_wc_conflict_reason_edited:
        if (operation == svn_wc_operation_update ||
            operation == svn_wc_operation_switch)
          *description = _("A file containing uncommitted changes was "
                           "found in the working copy.");
        else if (operation == svn_wc_operation_merge)
          *description = _("A file which differs from the corresponding "
                           "file on the merge source branch was found "
                           "in the working copy.");
        break;
      case svn_wc_conflict_reason_obstructed:
        *description = _("A file which already occupies this path was found "
                         "in the working copy.");
        break;
      case svn_wc_conflict_reason_unversioned:
        *description = _("An unversioned file was found in the working "
                         "copy.");
        break;
      case svn_wc_conflict_reason_deleted:
        *description = _("A deleted file was found in the working copy.");
        break;
      case svn_wc_conflict_reason_missing:
        if (operation == svn_wc_operation_update ||
            operation == svn_wc_operation_switch)
          *description = _("No such file was found in the working copy.");
        else if (operation == svn_wc_operation_merge)
          {
            /* ### display deleted revision */
            *description = _("No such file was found in the merge target "
                             "working copy.\nPerhaps the file has been "
                             "deleted or moved away in the repository's "
                             "history?");
          }
        break;
      case svn_wc_conflict_reason_added:
      case svn_wc_conflict_reason_replaced:
        {
          /* ### show more details about copies or replacements? */
          *description = _("A file scheduled to be added to the "
                           "repository in the next commit was found in "
                           "the working copy.");
        }
        break;
      case svn_wc_conflict_reason_moved_away:
        {
          const char *moved_to_abspath;
          svn_error_t *err;

          err = svn_wc__node_was_moved_away(&moved_to_abspath, NULL, 
                                            ctx->wc_ctx,
                                            conflict->local_abspath,
                                            scratch_pool,
                                            scratch_pool);
          if (err)
            {
              if (err->apr_err == SVN_ERR_WC_PATH_NOT_FOUND)
                {
                  moved_to_abspath = NULL;
                  svn_error_clear(err);
                }
              else
                return svn_error_trace(err);
            }
          if (operation == svn_wc_operation_update ||
              operation == svn_wc_operation_switch)
            {
              if (moved_to_abspath == NULL)
                {
                  /* The move no longer exists. */
                  *description = _("The file in the working copy had "
                                   "been moved away at the time this "
                                   "conflict was recorded.");
                }
              else
                {
                  const char *wcroot_abspath;

                  SVN_ERR(svn_wc__get_wcroot(&wcroot_abspath,
                                             ctx->wc_ctx,
                                             conflict->local_abspath,
                                             scratch_pool,
                                             scratch_pool));
                  *description = apr_psprintf(
                                   result_pool,
                                   _("The file in the working copy was "
                                     "moved away to\n'%s'."),
                                   svn_dirent_local_style(
                                     svn_dirent_skip_ancestor(
                                       wcroot_abspath,
                                       moved_to_abspath),
                                     scratch_pool));
                }
            }
          else if (operation == svn_wc_operation_merge)
            {
              if (moved_to_abspath == NULL)
                {
                  /* The move probably happened in branch history.
                   * This case cannot happen until we detect incoming
                   * moves, which we currently don't do. */
                  /* ### find deleted/moved revision? */
                  *description = _("The file in the working copy had "
                                   "been moved away at the time this "
                                   "conflict was recorded.");
                }
              else
                {
                  /* This is a local move in the working copy. */
                  const char *wcroot_abspath;

                  SVN_ERR(svn_wc__get_wcroot(&wcroot_abspath,
                                             ctx->wc_ctx,
                                             conflict->local_abspath,
                                             scratch_pool,
                                             scratch_pool));
                  *description = apr_psprintf(
                                   result_pool,
                                   _("The file in the working copy was "
                                     "moved away to\n'%s'."),
                                   svn_dirent_local_style(
                                     svn_dirent_skip_ancestor(
                                       wcroot_abspath,
                                       moved_to_abspath),
                                     scratch_pool));
                }
            }
          break;
        }
      case svn_wc_conflict_reason_moved_here:
        {
          const char *moved_from_abspath;

          SVN_ERR(svn_wc__node_was_moved_here(&moved_from_abspath, NULL, 
                                              ctx->wc_ctx,
                                              conflict->local_abspath,
                                              scratch_pool,
                                              scratch_pool));
          if (operation == svn_wc_operation_update ||
              operation == svn_wc_operation_switch)
            {
              if (moved_from_abspath == NULL)
                {
                  /* The move no longer exists. */
                  *description = _("A file had been moved here in the "
                                   "working copy at the time this "
                                   "conflict was recorded.");
                }
              else
                {
                  const char *wcroot_abspath;

                  SVN_ERR(svn_wc__get_wcroot(&wcroot_abspath,
                                             ctx->wc_ctx,
                                             conflict->local_abspath,
                                             scratch_pool,
                                             scratch_pool));
                  *description = apr_psprintf(
                                   result_pool,
                                   _("A file was moved here in the "
                                     "working copy from\n'%s'."),
                                   svn_dirent_local_style(
                                     svn_dirent_skip_ancestor(
                                       wcroot_abspath,
                                       moved_from_abspath),
                                     scratch_pool));
                }
            }
          else if (operation == svn_wc_operation_merge)
            {
              if (moved_from_abspath == NULL)
                {
                  /* The move probably happened in branch history.
                   * This case cannot happen until we detect incoming
                   * moves, which we currently don't do. */
                  /* ### find deleted/moved revision? */
                  *description = _("A file had been moved here in the "
                                   "working copy at the time this "
                                   "conflict was recorded.");
                }
              else
                {
                  const char *wcroot_abspath;

                  SVN_ERR(svn_wc__get_wcroot(&wcroot_abspath,
                                             ctx->wc_ctx,
                                             conflict->local_abspath,
                                             scratch_pool,
                                             scratch_pool));
                  /* This is a local move in the working copy. */
                  *description = apr_psprintf(
                                   result_pool,
                                   _("A file was moved here in the "
                                     "working copy from\n'%s'."),
                                   svn_dirent_local_style(
                                     svn_dirent_skip_ancestor(
                                       wcroot_abspath,
                                       moved_from_abspath),
                                     scratch_pool));
                }
            }
          break;
        }
    }

  return SVN_NO_ERROR;
}