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
typedef  int /*<<< orphan*/  svn_wc_notify_func_t ;
typedef  int /*<<< orphan*/  svn_wc_adm_access_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_delta_editor_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct compat_notify_baton_t {void* baton; int /*<<< orphan*/  func; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_DEPTH_INFINITY_OR_FILES (int /*<<< orphan*/ ) ; 
 struct compat_notify_baton_t* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  compat_call_notify_func ; 
 int /*<<< orphan*/ * svn_wc_get_update_editor3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct compat_notify_baton_t*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/  const**,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc_get_update_editor(svn_revnum_t *target_revision,
                         svn_wc_adm_access_t *anchor,
                         const char *target,
                         svn_boolean_t use_commit_times,
                         svn_boolean_t recurse,
                         svn_wc_notify_func_t notify_func,
                         void *notify_baton,
                         svn_cancel_func_t cancel_func,
                         void *cancel_baton,
                         const char *diff3_cmd,
                         const svn_delta_editor_t **editor,
                         void **edit_baton,
                         svn_wc_traversal_info_t *traversal_info,
                         apr_pool_t *pool)
{
  /* This baton must live beyond this function. Alloc on heap.  */
  struct compat_notify_baton_t *nb = apr_palloc(pool, sizeof(*nb));

  nb->func = notify_func;
  nb->baton = notify_baton;

  return svn_wc_get_update_editor3(target_revision, anchor, target,
                                   use_commit_times,
                                   SVN_DEPTH_INFINITY_OR_FILES(recurse), FALSE,
                                   FALSE, compat_call_notify_func, nb,
                                   cancel_func, cancel_baton, NULL, NULL,
                                   NULL, NULL,
                                   diff3_cmd, NULL, editor, edit_baton,
                                   traversal_info, pool);
}