#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/ * (* svn_repos_authz_func_t ) (void**,int /*<<< orphan*/ *,char const*,void*,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_root_t ;
struct TYPE_5__ {scalar_t__ change_kind; char* copyfrom_path; int /*<<< orphan*/  copyfrom_rev; void* copyfrom_known; } ;
typedef  TYPE_1__ svn_fs_path_change3_t ;
struct TYPE_6__ {scalar_t__ kind; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ svn_fs_dirent_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_editor_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
typedef  void* svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SVN_ERR_MALFUNCTION () ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 void* TRUE ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 TYPE_2__* apr_hash_this_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_checksum_sha1 ; 
 int /*<<< orphan*/ * svn_editor_add_directory (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_editor_add_file (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_fs_copied_from (int /*<<< orphan*/ *,char**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_dir_entries (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_file_checksum (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_file_contents (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_node_proplist (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_fs_path_change_delete ; 
 scalar_t__ svn_fs_path_change_replace ; 
 int /*<<< orphan*/ * svn_fs_revision_root (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_root_fs (int /*<<< orphan*/ *) ; 
 char* svn_fspath__join (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_hash_gets (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_file ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 char* svn_relpath_join (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
add_subdir_ev2(svn_fs_root_t *source_root,
               svn_fs_root_t *target_root,
               svn_editor_t *editor,
               const char *repos_relpath,
               const char *source_fspath,
               svn_repos_authz_func_t authz_read_func,
               void *authz_read_baton,
               apr_hash_t *changed_paths,
               apr_pool_t *result_pool,
               apr_pool_t *scratch_pool)
{
  apr_pool_t *iterpool = svn_pool_create(scratch_pool);
  apr_hash_index_t *hi;
  apr_hash_t *dirents;
  apr_hash_t *props = NULL;
  apr_array_header_t *children = NULL;

  SVN_ERR(svn_fs_node_proplist(&props, target_root, repos_relpath,
                               scratch_pool));

  SVN_ERR(svn_editor_add_directory(editor, repos_relpath, children,
                                   props, SVN_INVALID_REVNUM));

  /* We have to get the dirents from the source path, not the target,
     because we want nested copies from *readable* paths to be handled by
     path_driver_cb_func, not add_subdir (in order to preserve history). */
  SVN_ERR(svn_fs_dir_entries(&dirents, source_root, source_fspath,
                             scratch_pool));

  for (hi = apr_hash_first(scratch_pool, dirents); hi; hi = apr_hash_next(hi))
    {
      svn_fs_path_change3_t *change;
      svn_boolean_t readable = TRUE;
      svn_fs_dirent_t *dent = apr_hash_this_val(hi);
      const char *copyfrom_path = NULL;
      svn_revnum_t copyfrom_rev = SVN_INVALID_REVNUM;
      const char *child_relpath;

      svn_pool_clear(iterpool);

      child_relpath = svn_relpath_join(repos_relpath, dent->name, iterpool);

      /* If a file or subdirectory of the copied directory is listed as a
         changed path (because it was modified after the copy but before the
         commit), we remove it from the changed_paths hash so that future
         calls to path_driver_cb_func will ignore it. */
      change = svn_hash_gets(changed_paths, child_relpath);
      if (change)
        {
          svn_hash_sets(changed_paths, child_relpath, NULL);

          /* If it's a delete, skip this entry. */
          if (change->change_kind == svn_fs_path_change_delete)
            continue;

          /* If it's a replacement, check for copyfrom info (if we
             don't have it already. */
          if (change->change_kind == svn_fs_path_change_replace)
            {
              if (! change->copyfrom_known)
                {
                  SVN_ERR(svn_fs_copied_from(&change->copyfrom_rev,
                                             &change->copyfrom_path,
                                             target_root, child_relpath,
                                             result_pool));
                  change->copyfrom_known = TRUE;
                }
              copyfrom_path = change->copyfrom_path;
              copyfrom_rev = change->copyfrom_rev;
            }
        }

      if (authz_read_func)
        SVN_ERR(authz_read_func(&readable, target_root, child_relpath,
                                authz_read_baton, iterpool));

      if (! readable)
        continue;

      if (dent->kind == svn_node_dir)
        {
          svn_fs_root_t *new_source_root;
          const char *new_source_fspath;

          if (copyfrom_path)
            {
              svn_fs_t *fs = svn_fs_root_fs(source_root);
              SVN_ERR(svn_fs_revision_root(&new_source_root, fs,
                                           copyfrom_rev, result_pool));
              new_source_fspath = copyfrom_path;
            }
          else
            {
              new_source_root = source_root;
              new_source_fspath = svn_fspath__join(source_fspath, dent->name,
                                                   iterpool);
            }

          /* ### authz considerations?
           *
           * I think not; when path_driver_cb_func() calls add_subdir(), it
           * passes SOURCE_ROOT and SOURCE_FSPATH that are unreadable.
           */
          if (change && change->change_kind == svn_fs_path_change_replace
              && copyfrom_path == NULL)
            {
              SVN_ERR(svn_editor_add_directory(editor, child_relpath,
                                               children, props,
                                               SVN_INVALID_REVNUM));
            }
          else
            {
              SVN_ERR(add_subdir_ev2(new_source_root, target_root,
                                     editor, child_relpath,
                                     new_source_fspath,
                                     authz_read_func, authz_read_baton,
                                     changed_paths, result_pool, iterpool));
            }
        }
      else if (dent->kind == svn_node_file)
        {
          svn_checksum_t *checksum;
          svn_stream_t *contents;

          SVN_ERR(svn_fs_node_proplist(&props, target_root,
                                       child_relpath, iterpool));

          SVN_ERR(svn_fs_file_contents(&contents, target_root,
                                       child_relpath, iterpool));

          SVN_ERR(svn_fs_file_checksum(&checksum, svn_checksum_sha1,
                                       target_root,
                                       child_relpath, TRUE, iterpool));

          SVN_ERR(svn_editor_add_file(editor, child_relpath, checksum,
                                      contents, props, SVN_INVALID_REVNUM));
        }
      else
        SVN_ERR_MALFUNCTION();
    }

  svn_pool_destroy(iterpool);

  return SVN_NO_ERROR;
}