#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_txdelta_window_handler_t ;
typedef  int /*<<< orphan*/  svn_txdelta_stream_t ;
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/ * (* svn_repos_authz_func_t ) (void**,int /*<<< orphan*/ *,char const*,void*,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_root_t ;
struct TYPE_6__ {scalar_t__ change_kind; char* copyfrom_path; int /*<<< orphan*/  copyfrom_rev; void* copyfrom_known; } ;
typedef  TYPE_1__ svn_fs_path_change3_t ;
struct TYPE_7__ {scalar_t__ kind; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ svn_fs_dirent_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_8__ {int /*<<< orphan*/ * (* close_file ) (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * (* apply_textdelta ) (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ;int /*<<< orphan*/ * (* change_file_prop ) (void*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * (* add_file ) (char const*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ;int /*<<< orphan*/ * (* close_directory ) (void*,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * (* add_directory ) (char const*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ;int /*<<< orphan*/ * (* change_dir_prop ) (void*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_3__ svn_delta_editor_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
typedef  void* svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SVN_ERR_MALFUNCTION () ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 void* TRUE ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 void* apr_hash_this_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub1 (char const*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/ * stub2 (void*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub3 (char const*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/ * stub4 (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub5 (char const*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/ * stub6 (void*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub7 (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/ * stub8 (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_checksum_md5 ; 
 int /*<<< orphan*/  svn_checksum_to_cstring (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_copied_from (int /*<<< orphan*/ *,char**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_dir_entries (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_file_checksum (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_get_file_delta_stream (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
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
 int /*<<< orphan*/ * svn_txdelta_send_txstream (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
add_subdir(svn_fs_root_t *source_root,
           svn_fs_root_t *target_root,
           const svn_delta_editor_t *editor,
           void *edit_baton,
           const char *edit_path,
           void *parent_baton,
           const char *source_fspath,
           svn_repos_authz_func_t authz_read_func,
           void *authz_read_baton,
           apr_hash_t *changed_paths,
           apr_pool_t *pool,
           void **dir_baton)
{
  apr_pool_t *subpool = svn_pool_create(pool);
  apr_hash_index_t *hi, *phi;
  apr_hash_t *dirents;
  apr_hash_t *props;

  SVN_ERR(editor->add_directory(edit_path, parent_baton, NULL,
                                SVN_INVALID_REVNUM, pool, dir_baton));

  SVN_ERR(svn_fs_node_proplist(&props, target_root, edit_path, pool));

  for (phi = apr_hash_first(pool, props); phi; phi = apr_hash_next(phi))
    {
      const char *key = apr_hash_this_key(phi);
      svn_string_t *val = apr_hash_this_val(phi);

      svn_pool_clear(subpool);
      SVN_ERR(editor->change_dir_prop(*dir_baton, key, val, subpool));
    }

  /* We have to get the dirents from the source path, not the target,
     because we want nested copies from *readable* paths to be handled by
     path_driver_cb_func, not add_subdir (in order to preserve history). */
  SVN_ERR(svn_fs_dir_entries(&dirents, source_root, source_fspath, pool));

  for (hi = apr_hash_first(pool, dirents); hi; hi = apr_hash_next(hi))
    {
      svn_fs_path_change3_t *change;
      svn_boolean_t readable = TRUE;
      svn_fs_dirent_t *dent = apr_hash_this_val(hi);
      const char *copyfrom_path = NULL;
      svn_revnum_t copyfrom_rev = SVN_INVALID_REVNUM;
      const char *new_edit_path;

      svn_pool_clear(subpool);

      new_edit_path = svn_relpath_join(edit_path, dent->name, subpool);

      /* If a file or subdirectory of the copied directory is listed as a
         changed path (because it was modified after the copy but before the
         commit), we remove it from the changed_paths hash so that future
         calls to path_driver_cb_func will ignore it. */
      change = svn_hash_gets(changed_paths, new_edit_path);
      if (change)
        {
          svn_hash_sets(changed_paths, new_edit_path, NULL);

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
                                             target_root, new_edit_path, pool));
                  change->copyfrom_known = TRUE;
                }
              copyfrom_path = change->copyfrom_path;
              copyfrom_rev = change->copyfrom_rev;
            }
        }

      if (authz_read_func)
        SVN_ERR(authz_read_func(&readable, target_root, new_edit_path,
                                authz_read_baton, pool));

      if (! readable)
        continue;

      if (dent->kind == svn_node_dir)
        {
          svn_fs_root_t *new_source_root;
          const char *new_source_fspath;
          void *new_dir_baton;

          if (copyfrom_path)
            {
              svn_fs_t *fs = svn_fs_root_fs(source_root);
              SVN_ERR(svn_fs_revision_root(&new_source_root, fs,
                                           copyfrom_rev, pool));
              new_source_fspath = copyfrom_path;
            }
          else
            {
              new_source_root = source_root;
              new_source_fspath = svn_fspath__join(source_fspath, dent->name,
                                                   subpool);
            }

          /* ### authz considerations?
           *
           * I think not; when path_driver_cb_func() calls add_subdir(), it
           * passes SOURCE_ROOT and SOURCE_FSPATH that are unreadable.
           */
          if (change && change->change_kind == svn_fs_path_change_replace
              && copyfrom_path == NULL)
            {
              SVN_ERR(editor->add_directory(new_edit_path, *dir_baton,
                                            NULL, SVN_INVALID_REVNUM,
                                            subpool, &new_dir_baton));
            }
          else
            {
              SVN_ERR(add_subdir(new_source_root, target_root,
                                 editor, edit_baton, new_edit_path,
                                 *dir_baton, new_source_fspath,
                                 authz_read_func, authz_read_baton,
                                 changed_paths, subpool, &new_dir_baton));
            }

          SVN_ERR(editor->close_directory(new_dir_baton, subpool));
        }
      else if (dent->kind == svn_node_file)
        {
          svn_txdelta_window_handler_t delta_handler;
          void *delta_handler_baton, *file_baton;
          svn_txdelta_stream_t *delta_stream;
          svn_checksum_t *checksum;

          SVN_ERR(editor->add_file(new_edit_path, *dir_baton, NULL,
                                   SVN_INVALID_REVNUM, pool, &file_baton));

          SVN_ERR(svn_fs_node_proplist(&props, target_root,
                                       new_edit_path, subpool));

          for (phi = apr_hash_first(pool, props); phi; phi = apr_hash_next(phi))
            {
              const char *key = apr_hash_this_key(phi);
              svn_string_t *val = apr_hash_this_val(phi);

              SVN_ERR(editor->change_file_prop(file_baton, key, val, subpool));
            }

          SVN_ERR(editor->apply_textdelta(file_baton, NULL, pool,
                                          &delta_handler,
                                          &delta_handler_baton));

          SVN_ERR(svn_fs_get_file_delta_stream(&delta_stream, NULL, NULL,
                                               target_root, new_edit_path,
                                               pool));

          SVN_ERR(svn_txdelta_send_txstream(delta_stream,
                                            delta_handler,
                                            delta_handler_baton,
                                            pool));

          SVN_ERR(svn_fs_file_checksum(&checksum, svn_checksum_md5, target_root,
                                       new_edit_path, TRUE, pool));
          SVN_ERR(editor->close_file(file_baton,
                                     svn_checksum_to_cstring(checksum, pool),
                                     pool));
        }
      else
        SVN_ERR_MALFUNCTION();
    }

  svn_pool_destroy(subpool);

  return SVN_NO_ERROR;
}