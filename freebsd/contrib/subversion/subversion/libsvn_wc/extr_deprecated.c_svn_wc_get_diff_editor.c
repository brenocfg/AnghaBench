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
typedef  int /*<<< orphan*/  svn_wc_diff_callbacks_t ;
typedef  int /*<<< orphan*/  svn_wc_adm_access_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_delta_editor_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * svn_wc_get_diff_editor2 (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/  const**,void**,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc_get_diff_editor(svn_wc_adm_access_t *anchor,
                       const char *target,
                       const svn_wc_diff_callbacks_t *callbacks,
                       void *callback_baton,
                       svn_boolean_t recurse,
                       svn_boolean_t use_text_base,
                       svn_boolean_t reverse_order,
                       svn_cancel_func_t cancel_func,
                       void *cancel_baton,
                       const svn_delta_editor_t **editor,
                       void **edit_baton,
                       apr_pool_t *pool)
{
  return svn_wc_get_diff_editor2(anchor, target, callbacks, callback_baton,
                                 recurse, FALSE, use_text_base, reverse_order,
                                 cancel_func, cancel_baton,
                                 editor, edit_baton, pool);
}