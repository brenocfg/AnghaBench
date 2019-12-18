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
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_delta_path_driver_cb_func_t ;
typedef  int /*<<< orphan*/  svn_delta_editor_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  svn_delta_path_driver2 (int /*<<< orphan*/  const*,void*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 

svn_error_t *
svn_delta_path_driver(const svn_delta_editor_t *editor,
                      void *edit_baton,
                      svn_revnum_t revision,
                      const apr_array_header_t *paths,
                      svn_delta_path_driver_cb_func_t callback_func,
                      void *callback_baton,
                      apr_pool_t *scratch_pool)
{
  /* REVISION is dropped on the floor.  */

  return svn_error_trace(svn_delta_path_driver2(editor, edit_baton, paths,
                                                TRUE,
                                                callback_func, callback_baton,
                                                scratch_pool));
}