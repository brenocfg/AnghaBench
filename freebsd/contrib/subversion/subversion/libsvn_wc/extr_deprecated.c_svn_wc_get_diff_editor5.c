#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc_diff_callbacks3_t ;
typedef  int /*<<< orphan*/  svn_wc_context_t ;
typedef  int /*<<< orphan*/  svn_wc_adm_access_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  int /*<<< orphan*/  svn_delta_editor_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct diff_callbacks3_wrapper_baton {int /*<<< orphan*/  anchor_abspath; int /*<<< orphan*/  anchor; int /*<<< orphan*/ * db; void* baton; int /*<<< orphan*/  const* callbacks3; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 struct diff_callbacks3_wrapper_baton* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  diff_callbacks3_wrapper ; 
 int /*<<< orphan*/  svn_wc__adm_access_abspath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc__adm_get_db (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__context_create_with_db (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_adm_access_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_get_diff_editor6 (int /*<<< orphan*/  const**,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,struct diff_callbacks3_wrapper_baton*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc_get_diff_editor5(svn_wc_adm_access_t *anchor,
                        const char *target,
                        const svn_wc_diff_callbacks3_t *callbacks,
                        void *callback_baton,
                        svn_depth_t depth,
                        svn_boolean_t ignore_ancestry,
                        svn_boolean_t use_text_base,
                        svn_boolean_t reverse_order,
                        svn_cancel_func_t cancel_func,
                        void *cancel_baton,
                        const apr_array_header_t *changelist_filter,
                        const svn_delta_editor_t **editor,
                        void **edit_baton,
                        apr_pool_t *pool)
{
  struct diff_callbacks3_wrapper_baton *b = apr_palloc(pool, sizeof(*b));
  svn_wc_context_t *wc_ctx;
  svn_wc__db_t *db = svn_wc__adm_get_db(anchor);

  SVN_ERR(svn_wc__context_create_with_db(&wc_ctx, NULL, db, pool));

  b->callbacks3 = callbacks;
  b->baton = callback_baton;
  b->db = db;
  b->anchor = svn_wc_adm_access_path(anchor);
  b->anchor_abspath = svn_wc__adm_access_abspath(anchor);

  SVN_ERR(svn_wc_get_diff_editor6(editor,
                                   edit_baton,
                                   wc_ctx,
                                   b->anchor_abspath,
                                   target,
                                   depth,
                                   ignore_ancestry,
                                   FALSE,
                                   FALSE,
                                   use_text_base,
                                   reverse_order,
                                   FALSE,
                                   changelist_filter,
                                   &diff_callbacks3_wrapper,
                                   b,
                                   cancel_func,
                                   cancel_baton,
                                   pool,
                                   pool));

  /* Can't destroy wc_ctx. It is used by the diff editor */

   return SVN_NO_ERROR;
}