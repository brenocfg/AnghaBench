#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_17__ {int /*<<< orphan*/ * (* cb_add_file ) (int /*<<< orphan*/ ,char const*,TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_18__ {int /*<<< orphan*/  scratch_pool; int /*<<< orphan*/  baton; TYPE_1__ funcs; } ;
typedef  TYPE_2__ svn_editor_t ;
struct TYPE_19__ {scalar_t__ kind; } ;
typedef  TYPE_3__ svn_checksum_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_UNKNOWN_CHILD (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  CLEAR_INCOMPLETE (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  END_CALLBACK (TYPE_2__*) ; 
 int /*<<< orphan*/  MARK_COMPLETED (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  MARK_PARENT_STABLE (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  SHOULD_ALLOW_ADD (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  SHOULD_NOT_BE_FINISHED (TYPE_2__*) ; 
 int /*<<< orphan*/  START_CALLBACK (TYPE_2__*) ; 
 scalar_t__ SVN_EDITOR_CHECKSUM_KIND ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  VERIFY_PARENT_MAY_EXIST (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  check_cancel (TYPE_2__*) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ,char const*,TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ ) ; 
 int svn_relpath_is_canonical (char const*) ; 

svn_error_t *
svn_editor_add_file(svn_editor_t *editor,
                    const char *relpath,
                    const svn_checksum_t *checksum,
                    svn_stream_t *contents,
                    apr_hash_t *props,
                    svn_revnum_t replaces_rev)
{
  svn_error_t *err = SVN_NO_ERROR;

  SVN_ERR_ASSERT(svn_relpath_is_canonical(relpath));
  SVN_ERR_ASSERT(checksum != NULL
                    && checksum->kind == SVN_EDITOR_CHECKSUM_KIND);
  SVN_ERR_ASSERT(contents != NULL);
  SVN_ERR_ASSERT(props != NULL);
  SHOULD_NOT_BE_FINISHED(editor);
  SHOULD_ALLOW_ADD(editor, relpath);
  VERIFY_PARENT_MAY_EXIST(editor, relpath);
  CHECK_UNKNOWN_CHILD(editor, relpath);

  SVN_ERR(check_cancel(editor));

  if (editor->funcs.cb_add_file)
    {
      START_CALLBACK(editor);
      err = editor->funcs.cb_add_file(editor->baton, relpath,
                                      checksum, contents, props,
                                      replaces_rev, editor->scratch_pool);
      END_CALLBACK(editor);
    }

  MARK_COMPLETED(editor, relpath);
  MARK_PARENT_STABLE(editor, relpath);
  CLEAR_INCOMPLETE(editor, relpath);

  svn_pool_clear(editor->scratch_pool);
  return svn_error_trace(err);
}