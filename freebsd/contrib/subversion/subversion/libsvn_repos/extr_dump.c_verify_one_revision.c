#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_repos_notify_func_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* close_edit ) (void*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ svn_delta_editor_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  get_dump_editor (TYPE_1__ const**,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_delta_get_cancellation_editor (int /*<<< orphan*/ ,void*,TYPE_1__ const*,void*,TYPE_1__ const**,void**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_revision_proplist2 (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_revision_root (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_verify_root (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos_replay2 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__ const*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verify_close_directory ; 

__attribute__((used)) static svn_error_t *
verify_one_revision(svn_fs_t *fs,
                    svn_revnum_t rev,
                    svn_repos_notify_func_t notify_func,
                    void *notify_baton,
                    svn_revnum_t start_rev,
                    svn_boolean_t check_normalization,
                    svn_cancel_func_t cancel_func,
                    void *cancel_baton,
                    apr_pool_t *scratch_pool)
{
  const svn_delta_editor_t *dump_editor;
  void *dump_edit_baton;
  svn_fs_root_t *to_root;
  apr_hash_t *props;
  const svn_delta_editor_t *cancel_editor;
  void *cancel_edit_baton;

  /* Get cancellable dump editor, but with our close_directory handler.*/
  SVN_ERR(get_dump_editor(&dump_editor, &dump_edit_baton,
                          fs, rev, "",
                          svn_stream_empty(scratch_pool),
                          NULL, NULL,
                          verify_close_directory,
                          notify_func, notify_baton,
                          start_rev,
                          FALSE, TRUE, /* use_deltas, verify */
                          check_normalization,
                          scratch_pool));
  SVN_ERR(svn_delta_get_cancellation_editor(cancel_func, cancel_baton,
                                            dump_editor, dump_edit_baton,
                                            &cancel_editor,
                                            &cancel_edit_baton,
                                            scratch_pool));
  SVN_ERR(svn_fs_revision_root(&to_root, fs, rev, scratch_pool));
  SVN_ERR(svn_fs_verify_root(to_root, scratch_pool));
  SVN_ERR(svn_repos_replay2(to_root, "", SVN_INVALID_REVNUM, FALSE,
                            cancel_editor, cancel_edit_baton,
                            NULL, NULL, scratch_pool));

  /* While our editor close_edit implementation is a no-op, we still
     do this for completeness. */
  SVN_ERR(cancel_editor->close_edit(cancel_edit_baton, scratch_pool));

  SVN_ERR(svn_fs_revision_proplist2(&props, fs, rev, FALSE, scratch_pool,
                                    scratch_pool));

  return SVN_NO_ERROR;
}