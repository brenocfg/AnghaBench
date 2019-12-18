#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_14__ {int /*<<< orphan*/ * (* cb_add_absent ) (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_15__ {int /*<<< orphan*/  scratch_pool; int /*<<< orphan*/  baton; TYPE_1__ funcs; } ;
typedef  TYPE_2__ svn_editor_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_UNKNOWN_CHILD (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  CLEAR_INCOMPLETE (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  END_CALLBACK (TYPE_2__*) ; 
 int /*<<< orphan*/  MARK_COMPLETED (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  MARK_PARENT_STABLE (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  SHOULD_ALLOW_ADD (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  SHOULD_NOT_BE_FINISHED (TYPE_2__*) ; 
 int /*<<< orphan*/  START_CALLBACK (TYPE_2__*) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  VERIFY_PARENT_MAY_EXIST (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  check_cancel (TYPE_2__*) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_relpath_is_canonical (char const*) ; 

svn_error_t *
svn_editor_add_absent(svn_editor_t *editor,
                      const char *relpath,
                      svn_node_kind_t kind,
                      svn_revnum_t replaces_rev)
{
  svn_error_t *err = SVN_NO_ERROR;

  SVN_ERR_ASSERT(svn_relpath_is_canonical(relpath));
  SHOULD_NOT_BE_FINISHED(editor);
  SHOULD_ALLOW_ADD(editor, relpath);
  VERIFY_PARENT_MAY_EXIST(editor, relpath);
  CHECK_UNKNOWN_CHILD(editor, relpath);

  SVN_ERR(check_cancel(editor));

  if (editor->funcs.cb_add_absent)
    {
      START_CALLBACK(editor);
      err = editor->funcs.cb_add_absent(editor->baton, relpath, kind,
                                        replaces_rev, editor->scratch_pool);
      END_CALLBACK(editor);
    }

  MARK_COMPLETED(editor, relpath);
  MARK_PARENT_STABLE(editor, relpath);
  CLEAR_INCOMPLETE(editor, relpath);

  svn_pool_clear(editor->scratch_pool);
  return svn_error_trace(err);
}