#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_8__ {int /*<<< orphan*/ * (* cb_complete ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  scratch_pool; int /*<<< orphan*/  baton; TYPE_1__ funcs; int /*<<< orphan*/  pending_incomplete_children; } ;
typedef  TYPE_2__ svn_editor_t ;

/* Variables and functions */
 int /*<<< orphan*/  END_CALLBACK (TYPE_2__*) ; 
 int /*<<< orphan*/  MARK_FINISHED (TYPE_2__*) ; 
 int /*<<< orphan*/  SHOULD_NOT_BE_FINISHED (TYPE_2__*) ; 
 int /*<<< orphan*/  START_CALLBACK (TYPE_2__*) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ apr_hash_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ ) ; 

svn_error_t *
svn_editor_complete(svn_editor_t *editor)
{
  svn_error_t *err = SVN_NO_ERROR;

  SHOULD_NOT_BE_FINISHED(editor);
#ifdef ENABLE_ORDERING_CHECK
  SVN_ERR_ASSERT(apr_hash_count(editor->pending_incomplete_children) == 0);
#endif

  if (editor->funcs.cb_complete)
    {
      START_CALLBACK(editor);
      err = editor->funcs.cb_complete(editor->baton, editor->scratch_pool);
      END_CALLBACK(editor);
    }

  MARK_FINISHED(editor);

  svn_pool_clear(editor->scratch_pool);
  return svn_error_trace(err);
}