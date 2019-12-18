#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct editor_baton {int /*<<< orphan*/  edit_pool; int /*<<< orphan*/  changes; } ;
struct change_node {int /*<<< orphan*/  props; int /*<<< orphan*/  changing; int /*<<< orphan*/  kind; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 struct change_node* insert_change (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_node_dir ; 
 int /*<<< orphan*/  svn_prop_hash_dup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
alter_directory_cb(void *baton,
                   const char *relpath,
                   svn_revnum_t revision,
                   const apr_array_header_t *children,
                   apr_hash_t *props,
                   apr_pool_t *scratch_pool)
{
  struct editor_baton *eb = baton;
  struct change_node *change = insert_change(relpath, eb->changes);

  /* ### should we verify the kind is truly a directory?  */

  /* ### do we need to do anything with CHILDREN?  */

  /* Note: this node may already have information in CHANGE as a result
     of an earlier copy/move operation.  */
  change->kind = svn_node_dir;
  change->changing = revision;
  change->props = svn_prop_hash_dup(props, eb->edit_pool);

  return SVN_NO_ERROR;
}