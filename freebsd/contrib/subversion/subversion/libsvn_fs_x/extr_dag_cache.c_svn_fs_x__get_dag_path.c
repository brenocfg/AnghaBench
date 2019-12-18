#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stringbuf_t ;
struct TYPE_16__ {scalar_t__ len; } ;
typedef  TYPE_1__ svn_string_t ;
struct TYPE_17__ {int /*<<< orphan*/  copy_src_path; int /*<<< orphan*/  copy_inherit; int /*<<< orphan*/  node; } ;
typedef  TYPE_2__ svn_fs_x__dag_path_t ;
typedef  int /*<<< orphan*/  svn_fs_x__change_set_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
struct TYPE_18__ {int /*<<< orphan*/ * fs; } ;
typedef  TYPE_3__ svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  dag_node_t ;
typedef  scalar_t__ apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_FS__NOT_FOUND (TYPE_3__*,char const*) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  dag_step (int /*<<< orphan*/ **,TYPE_3__*,int /*<<< orphan*/ ,char const*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_copy_inheritance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_root_node (int /*<<< orphan*/ **,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* make_parent_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 char* next_entry_name (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  normalize_path (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  svn_fs_x__copy_id_inherit_self ; 
 scalar_t__ svn_fs_x__dag_node_kind (int /*<<< orphan*/ ) ; 
 int svn_fs_x__dag_path_allow_null ; 
 int svn_fs_x__dag_path_last_optional ; 
 int /*<<< orphan*/  svn_fs_x__root_change_set (TYPE_3__*) ; 
 scalar_t__ svn_node_dir ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stringbuf_create_ensure (int,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_x__get_dag_path(svn_fs_x__dag_path_t **dag_path_p,
                       svn_fs_root_t *root,
                       const char *fs_path,
                       int flags,
                       svn_boolean_t is_txn_path,
                       apr_pool_t *result_pool,
                       apr_pool_t *scratch_pool)
{
  svn_fs_t *fs = root->fs;
  dag_node_t *here = NULL; /* The directory we're currently looking at.  */
  svn_fs_x__dag_path_t *dag_path; /* The path from HERE up to the root. */
  apr_pool_t *iterpool = svn_pool_create(scratch_pool);

  svn_fs_x__change_set_t change_set = svn_fs_x__root_change_set(root);
  const char *entry;
  svn_string_t path;
  svn_stringbuf_t *entry_buffer = svn_stringbuf_create_ensure(64,
                                                              scratch_pool);
  apr_size_t path_len;

  /* Normalize the FS_PATH to be compatible with our DAG walk utils. */
  normalize_path(&path, fs_path); /* "" */

  /* Make a DAG_PATH for the root node, using its own current copy id.  */
  SVN_ERR(get_root_node(&here, root, change_set, iterpool));
  dag_path = make_parent_path(here, entry_buffer, NULL, result_pool);
  dag_path->copy_inherit = svn_fs_x__copy_id_inherit_self;

  path_len = path.len;
  path.len = 0;

  /* Walk the path segment by segment.  Add to the DAG_PATH as we go. */
  for (entry = next_entry_name(&path, entry_buffer);
       entry;
       entry = next_entry_name(&path, entry_buffer))
    {
      svn_pool_clear(iterpool);

      /* If the current node is not a directory and we are just here to
       * check for the path's existence, then that's o.k.
       * Otherwise, non-dir nodes will cause an error in dag_step. */
      if (   (flags & svn_fs_x__dag_path_allow_null)
          && (svn_fs_x__dag_node_kind(dag_path->node) != svn_node_dir))
        {
          dag_path = NULL;
          break;
        }

      /* Find the sub-node. */
      SVN_ERR(dag_step(&here, root, dag_path->node, entry, &path, change_set,
                       TRUE, iterpool));

      /* "node not found" requires special handling.  */
      if (here == NULL)
        {
          /* If this was the last path component, and the caller
             said it was optional, then don't return an error;
             just put a NULL node pointer in the path. 
           */
          if ((flags & svn_fs_x__dag_path_last_optional)
              && (path_len == path.len))
            {
              dag_path = make_parent_path(NULL, entry_buffer, dag_path,
                                          result_pool);
              break;
            }
          else if (flags & svn_fs_x__dag_path_allow_null)
            {
              dag_path = NULL;
              break;
            }
          else
            {
              /* Build a better error message than svn_fs_x__dag_open
                 can provide, giving the root and full path name.  */
              return SVN_FS__NOT_FOUND(root, fs_path);
            }
        }

      /* Now, make a parent_path item for CHILD. */
      dag_path = make_parent_path(here, entry_buffer, dag_path, result_pool);
      if (is_txn_path)
        {
          SVN_ERR(get_copy_inheritance(&dag_path->copy_inherit,
                                       &dag_path->copy_src_path,
                                       fs, dag_path, iterpool));
        }
    }

  svn_pool_destroy(iterpool);
  *dag_path_p = dag_path;
  return SVN_NO_ERROR;
}