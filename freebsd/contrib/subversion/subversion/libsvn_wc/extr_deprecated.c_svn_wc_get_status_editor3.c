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
typedef  int /*<<< orphan*/  svn_wc_traversal_info_t ;
typedef  int /*<<< orphan*/  svn_wc_status_func2_t ;
typedef  int /*<<< orphan*/  svn_wc_adm_access_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  int /*<<< orphan*/  svn_delta_editor_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct status_editor3_compat_baton {void* old_baton; int /*<<< orphan*/  old_func; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 struct status_editor3_compat_baton* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  status_editor3_compat_func ; 
 int /*<<< orphan*/ * svn_wc_get_status_editor4 (int /*<<< orphan*/  const**,void**,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,struct status_editor3_compat_baton*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc_get_status_editor3(const svn_delta_editor_t **editor,
                          void **edit_baton,
                          void **set_locks_baton,
                          svn_revnum_t *edit_revision,
                          svn_wc_adm_access_t *anchor,
                          const char *target,
                          svn_depth_t depth,
                          svn_boolean_t get_all,
                          svn_boolean_t no_ignore,
                          const apr_array_header_t *ignore_patterns,
                          svn_wc_status_func2_t status_func,
                          void *status_baton,
                          svn_cancel_func_t cancel_func,
                          void *cancel_baton,
                          svn_wc_traversal_info_t *traversal_info,
                          apr_pool_t *pool)
{
  /* This baton must live beyond this function. Alloc on heap.  */
  struct status_editor3_compat_baton *secb = apr_palloc(pool, sizeof(*secb));

  secb->old_func = status_func;
  secb->old_baton = status_baton;

  return svn_wc_get_status_editor4(editor, edit_baton, set_locks_baton,
                                   edit_revision, anchor, target, depth,
                                   get_all, no_ignore, ignore_patterns,
                                   status_editor3_compat_func, secb,
                                   cancel_func, cancel_baton, traversal_info,
                                   pool);
}