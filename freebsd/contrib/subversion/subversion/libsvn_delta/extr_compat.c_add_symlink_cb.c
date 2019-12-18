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
struct change_node {int /*<<< orphan*/  props; int /*<<< orphan*/  deleting; int /*<<< orphan*/  kind; int /*<<< orphan*/  action; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  RESTRUCTURE_ADD ; 
 int /*<<< orphan*/  SVN__NOT_IMPLEMENTED () ; 
 struct change_node* insert_change (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_node_symlink ; 
 int /*<<< orphan*/  svn_prop_hash_dup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
add_symlink_cb(void *baton,
               const char *relpath,
               const char *target,
               apr_hash_t *props,
               svn_revnum_t replaces_rev,
               apr_pool_t *scratch_pool)
{
#if 0
  struct editor_baton *eb = baton;
  struct change_node *change = insert_change(relpath, eb->changes);

  change->action = RESTRUCTURE_ADD;
  change->kind = svn_node_symlink;
  change->deleting = replaces_rev;
  change->props = svn_prop_hash_dup(props, eb->edit_pool);
  /* ### target  */
#endif

  SVN__NOT_IMPLEMENTED();
}