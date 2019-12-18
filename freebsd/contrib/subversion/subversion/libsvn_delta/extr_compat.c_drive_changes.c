#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_2__ {int /*<<< orphan*/ * baton; } ;
struct editor_baton {int /*<<< orphan*/  dedit_baton; int /*<<< orphan*/  deditor; int /*<<< orphan*/  base_relpath; int /*<<< orphan*/  changes; TYPE_1__ root; } ;
struct change_node {int /*<<< orphan*/  kind; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  apply_change ; 
 int /*<<< orphan*/ * get_sorted_paths (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct change_node* insert_change (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_delta_path_driver2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_node_dir ; 

__attribute__((used)) static svn_error_t *
drive_changes(const struct editor_baton *eb,
              apr_pool_t *scratch_pool)
{
  struct change_node *change;
  const apr_array_header_t *paths;

  /* If we never opened a root baton, then the caller aborted the editor
     before it even began. There is nothing to do. Bail.  */
  if (eb->root.baton == NULL)
    return SVN_NO_ERROR;

  /* We need to make the path driver believe we want to make changes to
     the root. Otherwise, it will attempt an open_root(), which we already
     did in start_edit_func(). We can forge up a change record, if one
     does not already exist.  */
  change = insert_change(eb->base_relpath, eb->changes);
  change->kind = svn_node_dir;
  /* No property changes (tho they might exist from a real change).  */

  /* Get a sorted list of Ev1-relative paths.  */
  paths = get_sorted_paths(eb->changes, eb->base_relpath, scratch_pool);
  SVN_ERR(svn_delta_path_driver2(eb->deditor, eb->dedit_baton, paths,
                                 FALSE, apply_change, (void *)eb,
                                 scratch_pool));

  return SVN_NO_ERROR;
}