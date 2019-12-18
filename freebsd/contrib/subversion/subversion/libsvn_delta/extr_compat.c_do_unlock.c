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
typedef  int /*<<< orphan*/  svn_error_t ;
struct editor_baton {int /*<<< orphan*/  changes; } ;
struct change_node {int /*<<< orphan*/  unlock; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 struct change_node* insert_change (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
do_unlock(void *baton,
          const char *path,
          apr_pool_t *scratch_pool)
{
  struct editor_baton *eb = baton;

  {
    /* PATH is REPOS_RELPATH  */
    struct change_node *change = insert_change(path, eb->changes);

    /* We will need to propagate a deletion of SVN_PROP_ENTRY_LOCK_TOKEN  */
    change->unlock = TRUE;
  }

  return SVN_NO_ERROR;
}