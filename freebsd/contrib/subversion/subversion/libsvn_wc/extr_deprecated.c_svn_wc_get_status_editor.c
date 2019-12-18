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
typedef  int /*<<< orphan*/  svn_wc_status_func_t ;
typedef  int /*<<< orphan*/  svn_wc_adm_access_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_delta_editor_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct old_status_func_cb_baton {void* original_baton; int /*<<< orphan*/  original_func; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_DEPTH_INFINITY_OR_IMMEDIATES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 struct old_status_func_cb_baton* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  old_status_func_cb ; 
 int /*<<< orphan*/  svn_wc_get_default_ignores (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc_get_status_editor3 (int /*<<< orphan*/  const**,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct old_status_func_cb_baton*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc_get_status_editor(const svn_delta_editor_t **editor,
                         void **edit_baton,
                         svn_revnum_t *edit_revision,
                         svn_wc_adm_access_t *anchor,
                         const char *target,
                         apr_hash_t *config,
                         svn_boolean_t recurse,
                         svn_boolean_t get_all,
                         svn_boolean_t no_ignore,
                         svn_wc_status_func_t status_func,
                         void *status_baton,
                         svn_cancel_func_t cancel_func,
                         void *cancel_baton,
                         svn_wc_traversal_info_t *traversal_info,
                         apr_pool_t *pool)
{
  struct old_status_func_cb_baton *b = apr_pcalloc(pool, sizeof(*b));
  apr_array_header_t *ignores;
  b->original_func = status_func;
  b->original_baton = status_baton;
  SVN_ERR(svn_wc_get_default_ignores(&ignores, config, pool));
  return svn_wc_get_status_editor3(editor, edit_baton, NULL, edit_revision,
                                   anchor, target,
                                   SVN_DEPTH_INFINITY_OR_IMMEDIATES(recurse),
                                   get_all, no_ignore, ignores,
                                   old_status_func_cb, b,
                                   cancel_func, cancel_baton,
                                   traversal_info, pool);
}