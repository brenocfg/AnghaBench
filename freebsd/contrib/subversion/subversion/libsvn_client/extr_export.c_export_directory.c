#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_ra_session_t ;
struct TYPE_10__ {int /*<<< orphan*/  (* finish_report ) (void*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* set_path ) (void*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ svn_ra_reporter3_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  int /*<<< orphan*/  svn_delta_editor_t ;
struct TYPE_11__ {int /*<<< orphan*/  notify_baton2; int /*<<< orphan*/  notify_func2; } ;
typedef  TYPE_2__ svn_client_ctx_t ;
struct TYPE_12__ {int /*<<< orphan*/  rev; } ;
typedef  TYPE_3__ svn_client__pathrev_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct edit_baton {int /*<<< orphan*/  repos_root_url; int /*<<< orphan*/  externals; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENABLE_EV2_IMPL ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  get_editor_ev1 (int /*<<< orphan*/  const**,void**,struct edit_baton*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_editor_ev2 (int /*<<< orphan*/  const**,void**,struct edit_baton*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  open_root_internal (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (void*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client__export_externals (int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_depth_infinity ; 
 int /*<<< orphan*/  svn_dirent_get_absolute (char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_check_path (char const*,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_none ; 
 int /*<<< orphan*/  svn_path_is_url (char const*) ; 
 int /*<<< orphan*/  svn_ra_do_update3 (int /*<<< orphan*/ *,TYPE_1__ const**,void**,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
export_directory(const char *from_url,
                 const char *to_path,
                 struct edit_baton *eb,
                 svn_client__pathrev_t *loc,
                 svn_ra_session_t *ra_session,
                 svn_boolean_t overwrite,
                 svn_boolean_t ignore_externals,
                 svn_boolean_t ignore_keywords,
                 svn_depth_t depth,
                 const char *native_eol,
                 svn_client_ctx_t *ctx,
                 apr_pool_t *scratch_pool)
{
  void *edit_baton;
  const svn_delta_editor_t *export_editor;
  const svn_ra_reporter3_t *reporter;
  void *report_baton;
  svn_node_kind_t kind;

  SVN_ERR_ASSERT(svn_path_is_url(from_url));

  if (!ENABLE_EV2_IMPL)
    SVN_ERR(get_editor_ev1(&export_editor, &edit_baton, eb, ctx,
                           scratch_pool, scratch_pool));
  else
    SVN_ERR(get_editor_ev2(&export_editor, &edit_baton, eb, ctx,
                           scratch_pool, scratch_pool));

  /* Manufacture a basic 'report' to the update reporter. */
  SVN_ERR(svn_ra_do_update3(ra_session,
                            &reporter, &report_baton,
                            loc->rev,
                            "", /* no sub-target */
                            depth,
                            FALSE, /* don't want copyfrom-args */
                            FALSE, /* don't want ignore_ancestry */
                            export_editor, edit_baton,
                            scratch_pool, scratch_pool));

  SVN_ERR(reporter->set_path(report_baton, "", loc->rev,
                             /* Depth is irrelevant, as we're
                                passing start_empty=TRUE anyway. */
                             svn_depth_infinity,
                             TRUE, /* "help, my dir is empty!" */
                             NULL, scratch_pool));

  SVN_ERR(reporter->finish_report(report_baton, scratch_pool));

  /* Special case: Due to our sly export/checkout method of updating an
   * empty directory, no target will have been created if the exported
   * item is itself an empty directory (export_editor->open_root never
   * gets called, because there are no "changes" to make to the empty
   * dir we reported to the repository).
   *
   * So we just create the empty dir manually; but we do it via
   * open_root_internal(), in order to get proper notification.
   */
  SVN_ERR(svn_io_check_path(to_path, &kind, scratch_pool));
  if (kind == svn_node_none)
    SVN_ERR(open_root_internal
            (to_path, overwrite, ctx->notify_func2,
             ctx->notify_baton2, scratch_pool));

  if (! ignore_externals && depth == svn_depth_infinity)
    {
      const char *to_abspath;

      SVN_ERR(svn_dirent_get_absolute(&to_abspath, to_path, scratch_pool));
      SVN_ERR(svn_client__export_externals(eb->externals,
                                           from_url,
                                           to_abspath, eb->repos_root_url,
                                           depth, native_eol,
                                           ignore_keywords,
                                           ctx, scratch_pool));
    }

  return SVN_NO_ERROR;
}