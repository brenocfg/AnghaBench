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
typedef  int /*<<< orphan*/  svn_error_t ;
struct ev2_edit_baton {int /*<<< orphan*/  editor; int /*<<< orphan*/  closed; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  run_ev2_actions (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_editor_abort (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
ev2_abort_edit(void *edit_baton,
               apr_pool_t *scratch_pool)
{
  struct ev2_edit_baton *eb = edit_baton;

  SVN_ERR(run_ev2_actions(edit_baton, scratch_pool));
  if (!eb->closed)
    return svn_error_trace(svn_editor_abort(eb->editor));
  else
    return SVN_NO_ERROR;
}