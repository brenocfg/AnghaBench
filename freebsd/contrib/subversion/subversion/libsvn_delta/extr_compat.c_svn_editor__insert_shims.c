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
struct TYPE_3__ {int /*<<< orphan*/  fetch_baton; int /*<<< orphan*/ * fetch_base_func; int /*<<< orphan*/ * fetch_props_func; int /*<<< orphan*/ * fetch_kind_func; } ;
typedef  TYPE_1__ svn_delta_shim_callbacks_t ;
typedef  int /*<<< orphan*/  svn_delta_editor_t ;
typedef  int /*<<< orphan*/  svn_delta__unlock_func_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct svn_delta__extra_baton {int dummy; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_delta__delta_from_editor (int /*<<< orphan*/  const**,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct svn_delta__extra_baton*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_delta__editor_from_delta (int /*<<< orphan*/ **,struct svn_delta__extra_baton**,int /*<<< orphan*/ *,void**,int /*<<< orphan*/  const*,void*,int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_editor__insert_shims(const svn_delta_editor_t **deditor_out,
                         void **dedit_baton_out,
                         const svn_delta_editor_t *deditor_in,
                         void *dedit_baton_in,
                         const char *repos_root,
                         const char *base_relpath,
                         svn_delta_shim_callbacks_t *shim_callbacks,
                         apr_pool_t *result_pool,
                         apr_pool_t *scratch_pool)
{
#ifndef ENABLE_EV2_SHIMS
  /* Shims disabled, just copy the editor and baton directly. */
  *deditor_out = deditor_in;
  *dedit_baton_out = dedit_baton_in;
#else
  /* Use our shim APIs to create an intermediate svn_editor_t, and then
     wrap that again back into a svn_delta_editor_t.  This introduces
     a lot of overhead. */
  svn_editor_t *editor;

  /* The "extra baton" is a set of functions and a baton which allows the
     shims to communicate additional events to each other.
     svn_delta__editor_from_delta() returns a pointer to this baton, which
     svn_delta__delta_from_editor() should then store. */
  struct svn_delta__extra_baton *exb;

  /* The reason this is a pointer is that we don't know the appropriate
     value until we start receiving paths.  So process_actions() sets the
     flag, which drive_tree() later consumes. */
  svn_boolean_t *found_abs_paths = apr_palloc(result_pool,
                                              sizeof(*found_abs_paths));

  svn_delta__unlock_func_t unlock_func;
  void *unlock_baton;

  SVN_ERR_ASSERT(shim_callbacks->fetch_kind_func != NULL);
  SVN_ERR_ASSERT(shim_callbacks->fetch_props_func != NULL);
  SVN_ERR_ASSERT(shim_callbacks->fetch_base_func != NULL);

  SVN_ERR(svn_delta__editor_from_delta(&editor, &exb,
                            &unlock_func, &unlock_baton,
                            deditor_in, dedit_baton_in,
                            found_abs_paths, repos_root, base_relpath,
                            NULL, NULL,
                            shim_callbacks->fetch_kind_func,
                            shim_callbacks->fetch_baton,
                            shim_callbacks->fetch_props_func,
                            shim_callbacks->fetch_baton,
                            result_pool, scratch_pool));
  SVN_ERR(svn_delta__delta_from_editor(deditor_out, dedit_baton_out, editor,
                            unlock_func, unlock_baton,
                            found_abs_paths,
                            repos_root, base_relpath,
                            shim_callbacks->fetch_props_func,
                            shim_callbacks->fetch_baton,
                            shim_callbacks->fetch_base_func,
                            shim_callbacks->fetch_baton,
                            exb, result_pool));

#endif
  return SVN_NO_ERROR;
}