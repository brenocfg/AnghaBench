#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_13__ {int /*<<< orphan*/ * (* cb_delete ) (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_14__ {int /*<<< orphan*/  scratch_pool; int /*<<< orphan*/  baton; TYPE_1__ funcs; } ;
typedef  TYPE_2__ svn_editor_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHILD_DELETIONS_ALLOWED (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  END_CALLBACK (TYPE_2__*) ; 
 int /*<<< orphan*/  MARK_COMPLETED (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  MARK_PARENT_STABLE (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  SHOULD_NOT_BE_COMPLETED (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  SHOULD_NOT_BE_FINISHED (TYPE_2__*) ; 
 int /*<<< orphan*/  START_CALLBACK (TYPE_2__*) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  VERIFY_PARENT_MAY_EXIST (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  check_cancel (TYPE_2__*) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_relpath_is_canonical (char const*) ; 

svn_error_t *
svn_editor_delete(svn_editor_t *editor,
                  const char *relpath,
                  svn_revnum_t revision)
{
  svn_error_t *err = SVN_NO_ERROR;

  SVN_ERR_ASSERT(svn_relpath_is_canonical(relpath));
  SHOULD_NOT_BE_FINISHED(editor);
  SHOULD_NOT_BE_COMPLETED(editor, relpath);
  VERIFY_PARENT_MAY_EXIST(editor, relpath);
  CHILD_DELETIONS_ALLOWED(editor, relpath);

  SVN_ERR(check_cancel(editor));

  if (editor->funcs.cb_delete)
    {
      START_CALLBACK(editor);
      err = editor->funcs.cb_delete(editor->baton, relpath, revision,
                                    editor->scratch_pool);
      END_CALLBACK(editor);
    }

  MARK_COMPLETED(editor, relpath);
  MARK_PARENT_STABLE(editor, relpath);

  svn_pool_clear(editor->scratch_pool);
  return svn_error_trace(err);
}