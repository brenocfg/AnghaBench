#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  fs; } ;
typedef  TYPE_1__ svn_repos_t ;
typedef  int /*<<< orphan*/  svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_7__ {void* change_dir_prop; void* change_file_prop; int /*<<< orphan*/  apply_textdelta; int /*<<< orphan*/  open_file; int /*<<< orphan*/  add_file; int /*<<< orphan*/  open_directory; int /*<<< orphan*/  add_directory; int /*<<< orphan*/  delete_entry; int /*<<< orphan*/  open_root; } ;
typedef  TYPE_2__ svn_delta_editor_t ;
struct edit_baton {int /*<<< orphan*/ * base_root; int /*<<< orphan*/ * root; int /*<<< orphan*/  fs; int /*<<< orphan*/ * node_pool; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  add_directory ; 
 int /*<<< orphan*/  add_file ; 
 int /*<<< orphan*/  apply_textdelta ; 
 struct edit_baton* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 void* change_node_prop ; 
 int /*<<< orphan*/  delete_entry ; 
 int /*<<< orphan*/  open_directory ; 
 int /*<<< orphan*/  open_file ; 
 int /*<<< orphan*/  open_root ; 
 TYPE_2__* svn_delta_default_editor (int /*<<< orphan*/ *) ; 

svn_error_t *
svn_repos_node_editor(const svn_delta_editor_t **editor,
                      void **edit_baton,
                      svn_repos_t *repos,
                      svn_fs_root_t *base_root,
                      svn_fs_root_t *root,
                      apr_pool_t *node_pool,
                      apr_pool_t *pool)
{
  svn_delta_editor_t *my_editor;
  struct edit_baton *my_edit_baton;

  /* Set up the editor. */
  my_editor = svn_delta_default_editor(pool);
  my_editor->open_root           = open_root;
  my_editor->delete_entry        = delete_entry;
  my_editor->add_directory       = add_directory;
  my_editor->open_directory      = open_directory;
  my_editor->add_file            = add_file;
  my_editor->open_file           = open_file;
  my_editor->apply_textdelta     = apply_textdelta;
  my_editor->change_file_prop    = change_node_prop;
  my_editor->change_dir_prop     = change_node_prop;

  /* Set up the edit baton. */
  my_edit_baton = apr_pcalloc(pool, sizeof(*my_edit_baton));
  my_edit_baton->node_pool = node_pool;
  my_edit_baton->fs = repos->fs;
  my_edit_baton->root = root;
  my_edit_baton->base_root = base_root;

  *editor = my_editor;
  *edit_baton = my_edit_baton;

  return SVN_NO_ERROR;
}