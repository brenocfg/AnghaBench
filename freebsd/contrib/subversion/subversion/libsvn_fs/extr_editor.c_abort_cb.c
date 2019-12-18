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
struct edit_baton {int /*<<< orphan*/ * txn; int /*<<< orphan*/ * root; int /*<<< orphan*/  completed; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_abort_txn (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_close_root (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
abort_cb(void *baton,
         apr_pool_t *scratch_pool)
{
  struct edit_baton *eb = baton;
  svn_error_t *err;

  /* Don't allow a following call to svn_fs_editor_commit().  */
  eb->completed = TRUE;

  if (eb->root != NULL)
    {
      svn_fs_close_root(eb->root);
      eb->root = NULL;
    }

  /* ### should we examine the error and attempt svn_fs_purge_txn() ?  */
  err = svn_fs_abort_txn(eb->txn, scratch_pool);

  /* For safety, clear the now-useless txn.  */
  eb->txn = NULL;

  return svn_error_trace(err);
}