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
struct TYPE_13__ {int /*<<< orphan*/ * (* cb_copy ) (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_14__ {int /*<<< orphan*/  scratch_pool; int /*<<< orphan*/  baton; TYPE_1__ funcs; } ;
typedef  TYPE_2__ svn_editor_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_INCOMPLETE (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  END_CALLBACK (TYPE_2__*) ; 
 int /*<<< orphan*/  MARK_ALLOW_ALTER (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  MARK_PARENT_STABLE (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  SHOULD_ALLOW_ADD (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  SHOULD_NOT_BE_FINISHED (TYPE_2__*) ; 
 int /*<<< orphan*/  START_CALLBACK (TYPE_2__*) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  VERIFY_PARENT_MAY_EXIST (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  check_cancel (TYPE_2__*) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_relpath_is_canonical (char const*) ; 

svn_error_t *
svn_editor_copy(svn_editor_t *editor,
                const char *src_relpath,
                svn_revnum_t src_revision,
                const char *dst_relpath,
                svn_revnum_t replaces_rev)
{
  svn_error_t *err = SVN_NO_ERROR;

  SVN_ERR_ASSERT(svn_relpath_is_canonical(src_relpath));
  SVN_ERR_ASSERT(svn_relpath_is_canonical(dst_relpath));
  SHOULD_NOT_BE_FINISHED(editor);
  SHOULD_ALLOW_ADD(editor, dst_relpath);
  VERIFY_PARENT_MAY_EXIST(editor, src_relpath);
  VERIFY_PARENT_MAY_EXIST(editor, dst_relpath);

  SVN_ERR(check_cancel(editor));

  if (editor->funcs.cb_copy)
    {
      START_CALLBACK(editor);
      err = editor->funcs.cb_copy(editor->baton, src_relpath, src_revision,
                                  dst_relpath, replaces_rev,
                                  editor->scratch_pool);
      END_CALLBACK(editor);
    }

  MARK_ALLOW_ALTER(editor, dst_relpath);
  MARK_PARENT_STABLE(editor, dst_relpath);
  CLEAR_INCOMPLETE(editor, dst_relpath);

  svn_pool_clear(editor->scratch_pool);
  return svn_error_trace(err);
}