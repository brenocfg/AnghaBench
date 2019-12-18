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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_editor_t ;
typedef  int /*<<< orphan*/  svn_delta_editor_t ;
struct TYPE_3__ {int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/  cancel_func; } ;
typedef  TYPE_1__ svn_client_ctx_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct svn_delta__extra_baton {int /*<<< orphan*/  target_revision; struct edit_baton* baton; } ;
struct edit_baton {int /*<<< orphan*/  notify_baton; int /*<<< orphan*/  notify_func; int /*<<< orphan*/  force; int /*<<< orphan*/  root_path; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  add_directory_ev2 ; 
 int /*<<< orphan*/  add_file_ev2 ; 
 int /*<<< orphan*/ * apr_palloc (int /*<<< orphan*/ *,int) ; 
 struct svn_delta__extra_baton* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fetch_base_func ; 
 int /*<<< orphan*/  fetch_props_func ; 
 int /*<<< orphan*/  open_root_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_delta__delta_from_editor (int /*<<< orphan*/  const**,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct edit_baton*,int /*<<< orphan*/ ,struct edit_baton*,struct svn_delta__extra_baton*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_editor_create (int /*<<< orphan*/ **,struct edit_baton*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_editor_setcb_add_directory (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_editor_setcb_add_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  target_revision_func ; 

__attribute__((used)) static svn_error_t *
get_editor_ev2(const svn_delta_editor_t **export_editor,
               void **edit_baton,
               struct edit_baton *eb,
               svn_client_ctx_t *ctx,
               apr_pool_t *result_pool,
               apr_pool_t *scratch_pool)
{
  svn_editor_t *editor;
  struct svn_delta__extra_baton *exb = apr_pcalloc(result_pool, sizeof(*exb));
  svn_boolean_t *found_abs_paths = apr_palloc(result_pool,
                                              sizeof(*found_abs_paths));

  exb->baton = eb;
  exb->target_revision = target_revision_func;

  SVN_ERR(svn_editor_create(&editor, eb, ctx->cancel_func, ctx->cancel_baton,
                            result_pool, scratch_pool));
  SVN_ERR(svn_editor_setcb_add_directory(editor, add_directory_ev2,
                                         scratch_pool));
  SVN_ERR(svn_editor_setcb_add_file(editor, add_file_ev2, scratch_pool));

  *found_abs_paths = TRUE;

  SVN_ERR(svn_delta__delta_from_editor(export_editor, edit_baton,
                                       editor, NULL, NULL, found_abs_paths,
                                       NULL, NULL,
                                       fetch_props_func, eb,
                                       fetch_base_func, eb,
                                       exb, result_pool));

  /* Create the root of the export. */
  SVN_ERR(open_root_internal(eb->root_path, eb->force, eb->notify_func,
                             eb->notify_baton, scratch_pool));

  return SVN_NO_ERROR;
}