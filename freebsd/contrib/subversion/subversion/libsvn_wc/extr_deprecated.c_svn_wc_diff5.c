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
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct diff_callbacks3_wrapper_baton {int /*<<< orphan*/  anchor_abspath; int /*<<< orphan*/  anchor; void* baton; int /*<<< orphan*/  const* callbacks3; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 struct diff_callbacks3_wrapper_baton* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  diff_callbacks3_wrapper ; 
 int /*<<< orphan*/  svn_dirent_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_wc__adm_access_abspath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc__adm_get_db (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__context_create_with_db (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_adm_access_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_context_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_diff6 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct diff_callbacks3_wrapper_baton*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc_diff5(svn_wc_adm_access_t *anchor,
             const char *target,
             const svn_wc_diff_callbacks3_t *callbacks,
             void *callback_baton,
             svn_depth_t depth,
             svn_boolean_t ignore_ancestry,
             const apr_array_header_t *changelist_filter,
             apr_pool_t *pool)
{
  struct diff_callbacks3_wrapper_baton *b = apr_palloc(pool, sizeof(*b));
  svn_wc_context_t *wc_ctx;
  svn_wc__db_t *db = svn_wc__adm_get_db(anchor);

  SVN_ERR(svn_wc__context_create_with_db(&wc_ctx, NULL, db, pool));

  b->callbacks3 = callbacks;
  b->baton = callback_baton;
  b->anchor = svn_wc_adm_access_path(anchor);
  b->anchor_abspath = svn_wc__adm_access_abspath(anchor);

  SVN_ERR(svn_wc_diff6(wc_ctx,
                       svn_dirent_join(b->anchor_abspath, target, pool),
                       &diff_callbacks3_wrapper,
                       b,
                       depth,
                       ignore_ancestry,
                       FALSE,
                       FALSE,
                       changelist_filter,
                       NULL, NULL,
                       pool));

  return svn_error_trace(svn_wc_context_destroy(wc_ctx));
}