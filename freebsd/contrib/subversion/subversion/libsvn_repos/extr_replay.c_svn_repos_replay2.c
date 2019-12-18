#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_repos_authz_func_t ;
typedef  int /*<<< orphan*/  svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_editor_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* set_target_revision ) (void*,scalar_t__,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ svn_delta_editor_t ;
typedef  int /*<<< orphan*/  svn_delta__unlock_func_t ;
typedef  scalar_t__ svn_boolean_t ;
struct svn_delta__extra_baton {int /*<<< orphan*/  baton; int /*<<< orphan*/  (* start_edit ) (int /*<<< orphan*/ ,scalar_t__) ;} ;
struct path_driver_cb_baton {char const* base_path; int /*<<< orphan*/ * pool; int /*<<< orphan*/  copies; int /*<<< orphan*/ * compare_root; scalar_t__ low_water_mark; void* authz_read_baton; int /*<<< orphan*/  authz_read_func; int /*<<< orphan*/ * changed_paths; int /*<<< orphan*/ * root; void* edit_baton; TYPE_1__ const* editor; } ;
struct copy_info {int dummy; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_IS_VALID_REVNUM (scalar_t__) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  apr_array_make (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  fetch_kind_func ; 
 int /*<<< orphan*/  fetch_props_func ; 
 int /*<<< orphan*/  get_relevant_changes (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  path_driver_cb_func ; 
 int /*<<< orphan*/  stub1 (void*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (void*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (void*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (void*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  svn_delta__editor_from_delta (int /*<<< orphan*/ **,struct svn_delta__extra_baton**,int /*<<< orphan*/ *,void**,TYPE_1__ const*,void*,scalar_t__*,char const*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_delta_path_driver2 (TYPE_1__ const*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct path_driver_cb_baton*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_fs_is_revision_root (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_revision_root (int /*<<< orphan*/ **,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_fs_revision_root_revision (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_root_fs (int /*<<< orphan*/ *) ; 
 scalar_t__ svn_fs_txn_root_base_revision (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos__replay_ev2 (int /*<<< orphan*/ *,char const*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_repos_replay2(svn_fs_root_t *root,
                  const char *base_path,
                  svn_revnum_t low_water_mark,
                  svn_boolean_t send_deltas,
                  const svn_delta_editor_t *editor,
                  void *edit_baton,
                  svn_repos_authz_func_t authz_read_func,
                  void *authz_read_baton,
                  apr_pool_t *pool)
{
#ifndef USE_EV2_IMPL
  apr_hash_t *changed_paths;
  apr_array_header_t *paths;
  struct path_driver_cb_baton cb_baton;

  /* Special-case r0, which we know is an empty revision; if we don't
     special-case it we might end up trying to compare it to "r-1". */
  if (svn_fs_is_revision_root(root) && svn_fs_revision_root_revision(root) == 0)
    {
      SVN_ERR(editor->set_target_revision(edit_baton, 0, pool));
      return SVN_NO_ERROR;
    }

  if (! base_path)
    base_path = "";
  else if (base_path[0] == '/')
    ++base_path;

  /* Fetch the paths changed under ROOT. */
  SVN_ERR(get_relevant_changes(&changed_paths, &paths, root, base_path,
                               authz_read_func, authz_read_baton,
                               pool, pool));

  /* If we were not given a low water mark, assume that everything is there,
     all the way back to revision 0. */
  if (! SVN_IS_VALID_REVNUM(low_water_mark))
    low_water_mark = 0;

  /* Initialize our callback baton. */
  cb_baton.editor = editor;
  cb_baton.edit_baton = edit_baton;
  cb_baton.root = root;
  cb_baton.changed_paths = changed_paths;
  cb_baton.authz_read_func = authz_read_func;
  cb_baton.authz_read_baton = authz_read_baton;
  cb_baton.base_path = base_path;
  cb_baton.low_water_mark = low_water_mark;
  cb_baton.compare_root = NULL;

  if (send_deltas)
    {
      SVN_ERR(svn_fs_revision_root(&cb_baton.compare_root,
                                   svn_fs_root_fs(root),
                                   svn_fs_is_revision_root(root)
                                     ? svn_fs_revision_root_revision(root) - 1
                                     : svn_fs_txn_root_base_revision(root),
                                   pool));
    }

  cb_baton.copies = apr_array_make(pool, 4, sizeof(struct copy_info *));
  cb_baton.pool = pool;

  /* Determine the revision to use throughout the edit, and call
     EDITOR's set_target_revision() function.  */
  if (svn_fs_is_revision_root(root))
    {
      svn_revnum_t revision = svn_fs_revision_root_revision(root);
      SVN_ERR(editor->set_target_revision(edit_baton, revision, pool));
    }

  /* Call the path-based editor driver. */
  return svn_delta_path_driver2(editor, edit_baton,
                                paths, TRUE,
                                path_driver_cb_func, &cb_baton, pool);
#else
  svn_editor_t *editorv2;
  struct svn_delta__extra_baton *exb;
  svn_delta__unlock_func_t unlock_func;
  svn_boolean_t send_abs_paths;
  const char *repos_root = "";
  void *unlock_baton;

  /* If we were not given a low water mark, assume that everything is there,
     all the way back to revision 0. */
  if (! SVN_IS_VALID_REVNUM(low_water_mark))
    low_water_mark = 0;

  /* Special-case r0, which we know is an empty revision; if we don't
     special-case it we might end up trying to compare it to "r-1". */
  if (svn_fs_is_revision_root(root)
        && svn_fs_revision_root_revision(root) == 0)
    {
      SVN_ERR(editor->set_target_revision(edit_baton, 0, pool));
      return SVN_NO_ERROR;
    }

  /* Determine the revision to use throughout the edit, and call
     EDITOR's set_target_revision() function.  */
  if (svn_fs_is_revision_root(root))
    {
      svn_revnum_t revision = svn_fs_revision_root_revision(root);
      SVN_ERR(editor->set_target_revision(edit_baton, revision, pool));
    }

  if (! base_path)
    base_path = "";
  else if (base_path[0] == '/')
    ++base_path;

  /* Use the shim to convert our editor to an Ev2 editor, and pass it down
     the stack. */
  SVN_ERR(svn_delta__editor_from_delta(&editorv2, &exb,
                                       &unlock_func, &unlock_baton,
                                       editor, edit_baton,
                                       &send_abs_paths,
                                       repos_root, "",
                                       NULL, NULL,
                                       fetch_kind_func, root,
                                       fetch_props_func, root,
                                       pool, pool));

  /* Tell the shim that we're starting the process. */
  SVN_ERR(exb->start_edit(exb->baton, svn_fs_revision_root_revision(root)));

  /* ### We're ignoring SEND_DELTAS here. */
  SVN_ERR(svn_repos__replay_ev2(root, base_path, low_water_mark,
                                editorv2, authz_read_func, authz_read_baton,
                                pool));

  return SVN_NO_ERROR;
#endif
}