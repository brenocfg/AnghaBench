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
struct edit_baton {int /*<<< orphan*/ * root; int /*<<< orphan*/  completed; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  svn_fs_close_root (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
complete_cb(void *baton,
            apr_pool_t *scratch_pool)
{
  struct edit_baton *eb = baton;

  /* Watch out for a following call to svn_fs_editor_commit(). Note that
     we are likely here because svn_fs_editor_commit() was called, and it
     invoked svn_editor_complete().  */
  eb->completed = TRUE;

  if (eb->root != NULL)
    {
      svn_fs_close_root(eb->root);
      eb->root = NULL;
    }

  return SVN_NO_ERROR;
}