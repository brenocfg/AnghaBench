#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {char const* data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
struct TYPE_21__ {scalar_t__ len; } ;
typedef  TYPE_2__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_fs_x__change_set_t ;
struct TYPE_22__ {int /*<<< orphan*/  is_txn_root; } ;
typedef  TYPE_3__ svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * dag_node_cache_get (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  dag_step (int /*<<< orphan*/ **,TYPE_3__*,int /*<<< orphan*/ *,char const*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ extract_last_segment (TYPE_2__*,TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  get_root_node (int /*<<< orphan*/ **,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* next_entry_name (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__root_change_set (TYPE_3__*) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_stringbuf_create_ensure (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_match_last_node (int /*<<< orphan*/ **,TYPE_3__*,TYPE_2__*) ; 

__attribute__((used)) static svn_error_t *
walk_dag_path(dag_node_t **node_p,
              svn_fs_root_t *root,
              svn_string_t *path,
              apr_pool_t *scratch_pool)
{
  dag_node_t *here = NULL; /* The directory we're currently looking at.  */
  apr_pool_t *iterpool;
  svn_fs_x__change_set_t change_set = svn_fs_x__root_change_set(root);
  const char *entry;
  svn_string_t directory;
  svn_stringbuf_t *entry_buffer;

  /* Special case: root directory.
     We will later assume that all paths have at least one parent level,
     so we must check here for those that don't. */
  if (path->len == 0)
    return svn_error_trace(get_root_node(node_p, root, change_set,
                                         scratch_pool));

  /* Callers often traverse the DAG in some path-based order or along the
     history segments.  That allows us to try a few guesses about where to
     find the next item.  This is only useful if the caller didn't request
     the full parent chain. */

  /* First attempt: Assume that we access the DAG for the same path as
     in the last lookup but for a different revision that happens to be
     the last revision that touched the respective node.  This is a
     common pattern when e.g. checking out over ra_serf.  Note that this
     will only work for committed data as the revision info for nodes in
     txns is bogus.

     This shortcut is quick and will exit this function upon success.
     So, try it first. */
  if (!root->is_txn_root)
    {
      SVN_ERR(try_match_last_node(node_p, root, path));

      /* Did the shortcut work? */
      if (*node_p)
          return SVN_NO_ERROR;
    }

  /* Second attempt: Try starting the lookup immediately at the parent
     node.  We will often have recently accessed either a sibling or
     said parent directory itself for the same revision.  ENTRY will
     point to the last '/' in PATH. */
  entry_buffer = svn_stringbuf_create_ensure(64, scratch_pool);
  if (extract_last_segment(path, &directory, entry_buffer))
    {
      here = dag_node_cache_get(root, &directory);

      /* Did the shortcut work? */
      if (here)
        return svn_error_trace(dag_step(node_p, root, here,
                                        entry_buffer->data, path,
                                        change_set, FALSE, scratch_pool));
    }

  /* Now there is something to iterate over. Thus, create the ITERPOOL. */
  iterpool = svn_pool_create(scratch_pool);

  /* Make a parent_path item for the root node, using its own current
     copy id.  */
  SVN_ERR(get_root_node(&here, root, change_set, iterpool));
  path->len = 0;

  /* Walk the path segment by segment. */
  for (entry = next_entry_name(path, entry_buffer);
       entry;
       entry = next_entry_name(path, entry_buffer))
    {
      svn_pool_clear(iterpool);

      /* Note that HERE is allocated from the DAG node cache and will
         therefore survive the ITERPOOL cleanup. */
      SVN_ERR(dag_step(&here, root, here, entry, path, change_set, FALSE,
                       iterpool));
    }

  svn_pool_destroy(iterpool);
  *node_p = here;

  return SVN_NO_ERROR;
}