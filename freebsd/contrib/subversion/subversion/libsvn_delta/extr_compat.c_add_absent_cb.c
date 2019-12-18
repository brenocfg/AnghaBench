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
typedef  int /*<<< orphan*/  svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct editor_baton {int /*<<< orphan*/  changes; } ;
struct change_node {int /*<<< orphan*/  deleting; int /*<<< orphan*/  kind; int /*<<< orphan*/  action; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  RESTRUCTURE_ADD_ABSENT ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 struct change_node* insert_change (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
add_absent_cb(void *baton,
              const char *relpath,
              svn_node_kind_t kind,
              svn_revnum_t replaces_rev,
              apr_pool_t *scratch_pool)
{
  struct editor_baton *eb = baton;
  struct change_node *change = insert_change(relpath, eb->changes);

  change->action = RESTRUCTURE_ADD_ABSENT;
  change->kind = kind;
  change->deleting = replaces_rev;

  return SVN_NO_ERROR;
}