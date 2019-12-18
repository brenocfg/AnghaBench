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
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_repos_authz_func_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_fs_root_t ;
typedef  scalar_t__ svn_fs_node_relation_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
struct TYPE_3__ {int /*<<< orphan*/ * (* close_edit ) (void*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* close_directory ) (void*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* open_root ) (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ;int /*<<< orphan*/  (* set_target_revision ) (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ svn_delta_editor_t ;
typedef  void* svn_boolean_t ;
struct context {void* ignore_ancestry; void* entry_props; void* text_deltas; void* authz_read_baton; int /*<<< orphan*/  authz_read_func; int /*<<< orphan*/ * target_root; int /*<<< orphan*/ * source_root; TYPE_1__ const* editor; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_NOT_DIRECTORY ; 
 int /*<<< orphan*/  SVN_ERR_FS_PATH_SYNTAX ; 
 int /*<<< orphan*/  SVN_ERR_REPOS_BAD_ARGS ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  add_file_or_dir (struct context*,void*,int /*<<< orphan*/ ,char const*,char const*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  authz_root_check (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  delete (struct context*,void*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  delta_dirs (struct context*,void*,int /*<<< orphan*/ ,char const*,char const*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_path_revision (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  replace_file_or_dir (struct context*,void*,int /*<<< orphan*/ ,char const*,char const*,char const*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  stub4 (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  stub5 (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  stub6 (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  stub7 (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  stub8 (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub9 (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_depth_exclude ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  svn_fs_check_path (scalar_t__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_fs_is_revision_root (int /*<<< orphan*/ *) ; 
 scalar_t__ svn_fs_is_txn_root (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_node_relation (scalar_t__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_fs_node_unchanged ; 
 scalar_t__ svn_fs_node_unrelated ; 
 int /*<<< orphan*/  svn_fs_refresh_revision_props (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_revision_root_revision (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_root_fs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_txn_root_base_revision (int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_none ; 
 char* svn_relpath_canonicalize (char const*,int /*<<< orphan*/ *) ; 
 char* svn_relpath_dirname (char const*,int /*<<< orphan*/ *) ; 
 char* svn_relpath_join (char const*,char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_repos_dir_delta2(svn_fs_root_t *src_root,
                     const char *src_parent_dir,
                     const char *src_entry,
                     svn_fs_root_t *tgt_root,
                     const char *tgt_fullpath,
                     const svn_delta_editor_t *editor,
                     void *edit_baton,
                     svn_repos_authz_func_t authz_read_func,
                     void *authz_read_baton,
                     svn_boolean_t text_deltas,
                     svn_depth_t depth,
                     svn_boolean_t entry_props,
                     svn_boolean_t ignore_ancestry,
                     apr_pool_t *pool)
{
  void *root_baton = NULL;
  struct context c;
  const char *src_fullpath;
  svn_node_kind_t src_kind, tgt_kind;
  svn_revnum_t rootrev;
  svn_fs_node_relation_t relation;
  const char *authz_root_path;

  /* SRC_PARENT_DIR must be valid. */
  if (src_parent_dir)
    src_parent_dir = svn_relpath_canonicalize(src_parent_dir, pool);
  else
    return svn_error_create(SVN_ERR_FS_NOT_DIRECTORY, 0,
                            "Invalid source parent directory '(null)'");

  /* TGT_FULLPATH must be valid. */
  if (tgt_fullpath)
    tgt_fullpath = svn_relpath_canonicalize(tgt_fullpath, pool);
  else
    return svn_error_create(SVN_ERR_FS_PATH_SYNTAX, 0,
                            _("Invalid target path"));

  if (depth == svn_depth_exclude)
    return svn_error_create(SVN_ERR_REPOS_BAD_ARGS, NULL,
                            _("Delta depth 'exclude' not supported"));

  /* Calculate the fs path implicitly used for editor->open_root, so
     we can do an authz check on that path first. */
  if (*src_entry)
    authz_root_path = svn_relpath_dirname(tgt_fullpath, pool);
  else
    authz_root_path = tgt_fullpath;

  /* Construct the full path of the source item. */
  src_fullpath = svn_relpath_join(src_parent_dir, src_entry, pool);

  /* Get the node kinds for the source and target paths.  */
  SVN_ERR(svn_fs_check_path(&tgt_kind, tgt_root, tgt_fullpath, pool));
  SVN_ERR(svn_fs_check_path(&src_kind, src_root, src_fullpath, pool));

  /* If neither of our paths exists, we don't really have anything to do. */
  if ((tgt_kind == svn_node_none) && (src_kind == svn_node_none))
    goto cleanup;

  /* If either the source or the target is a non-directory, we
     require that a SRC_ENTRY be supplied. */
  if ((! *src_entry) && ((src_kind != svn_node_dir)
                         || tgt_kind != svn_node_dir))
    return svn_error_create
      (SVN_ERR_FS_PATH_SYNTAX, 0,
       _("Invalid editor anchoring; at least one of the "
         "input paths is not a directory and there was no source entry"));

  /* Don't report / compare stale revprops.  However, revprop changes that
   * are made by a 3rd party outside this delta operation, may not be
   * detected as per our visibility guarantees.  Reset the revprop caches
   * for both roots in case they belong to different svn_fs_t instances. */
  SVN_ERR(svn_fs_refresh_revision_props(svn_fs_root_fs(tgt_root), pool));
  SVN_ERR(svn_fs_refresh_revision_props(svn_fs_root_fs(src_root), pool));

  /* Set the global target revision if one can be determined. */
  if (svn_fs_is_revision_root(tgt_root))
    {
      SVN_ERR(editor->set_target_revision
              (edit_baton, svn_fs_revision_root_revision(tgt_root), pool));
    }
  else if (svn_fs_is_txn_root(tgt_root))
    {
      SVN_ERR(editor->set_target_revision
              (edit_baton, svn_fs_txn_root_base_revision(tgt_root), pool));
    }

  /* Setup our pseudo-global structure here.  We need these variables
     throughout the deltafication process, so pass them around by
     reference to all the helper functions. */
  c.editor = editor;
  c.source_root = src_root;
  c.target_root = tgt_root;
  c.authz_read_func = authz_read_func;
  c.authz_read_baton = authz_read_baton;
  c.text_deltas = text_deltas;
  c.entry_props = entry_props;
  c.ignore_ancestry = ignore_ancestry;

  /* Get our editor root's revision. */
  rootrev = get_path_revision(src_root, src_parent_dir, pool);

  /* If one or the other of our paths doesn't exist, we have to handle
     those cases specially. */
  if (tgt_kind == svn_node_none)
    {
      /* Caller thinks that target still exists, but it doesn't.
         So transform their source path to "nothing" by deleting it. */
      SVN_ERR(authz_root_check(tgt_root, authz_root_path,
                               authz_read_func, authz_read_baton, pool));
      SVN_ERR(editor->open_root(edit_baton, rootrev, pool, &root_baton));
      SVN_ERR(delete(&c, root_baton, src_entry, pool));
      goto cleanup;
    }
  if (src_kind == svn_node_none)
    {
      /* The source path no longer exists, but the target does.
         So transform "nothing" into "something" by adding. */
      SVN_ERR(authz_root_check(tgt_root, authz_root_path,
                               authz_read_func, authz_read_baton, pool));
      SVN_ERR(editor->open_root(edit_baton, rootrev, pool, &root_baton));
      SVN_ERR(add_file_or_dir(&c, root_baton, depth, tgt_fullpath,
                              src_entry, tgt_kind, pool));
      goto cleanup;
    }

  /* Get and compare the node IDs for the source and target. */
  SVN_ERR(svn_fs_node_relation(&relation, tgt_root, tgt_fullpath,
                               src_root, src_fullpath, pool));

  if (relation == svn_fs_node_unchanged)
    {
      /* They are the same node!  No-op (you gotta love those). */
      goto cleanup;
    }
  else if (*src_entry)
    {
      /* If the nodes have different kinds, we must delete the one and
         add the other.  Also, if they are completely unrelated and
         our caller is interested in relatedness, we do the same thing. */
      if ((src_kind != tgt_kind)
          || ((relation == svn_fs_node_unrelated) && (! ignore_ancestry)))
        {
          SVN_ERR(authz_root_check(tgt_root, authz_root_path,
                                   authz_read_func, authz_read_baton, pool));
          SVN_ERR(editor->open_root(edit_baton, rootrev, pool, &root_baton));
          SVN_ERR(delete(&c, root_baton, src_entry, pool));
          SVN_ERR(add_file_or_dir(&c, root_baton, depth, tgt_fullpath,
                                  src_entry, tgt_kind, pool));
        }
      /* Otherwise, we just replace the one with the other. */
      else
        {
          SVN_ERR(authz_root_check(tgt_root, authz_root_path,
                                   authz_read_func, authz_read_baton, pool));
          SVN_ERR(editor->open_root(edit_baton, rootrev, pool, &root_baton));
          SVN_ERR(replace_file_or_dir(&c, root_baton, depth, src_fullpath,
                                      tgt_fullpath, src_entry,
                                      tgt_kind, pool));
        }
    }
  else
    {
      /* There is no entry given, so delta the whole parent directory. */
      SVN_ERR(authz_root_check(tgt_root, authz_root_path,
                               authz_read_func, authz_read_baton, pool));
      SVN_ERR(editor->open_root(edit_baton, rootrev, pool, &root_baton));
      SVN_ERR(delta_dirs(&c, root_baton, depth, src_fullpath,
                         tgt_fullpath, "", pool));
    }

 cleanup:

  /* Make sure we close the root directory if we opened one above. */
  if (root_baton)
    SVN_ERR(editor->close_directory(root_baton, pool));

  /* Close the edit. */
  return editor->close_edit(edit_baton, pool);
}