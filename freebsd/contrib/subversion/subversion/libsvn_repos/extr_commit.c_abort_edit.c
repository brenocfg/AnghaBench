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
struct edit_baton {int /*<<< orphan*/  txn; scalar_t__ txn_root; scalar_t__ txn_aborted; int /*<<< orphan*/  txn_owner; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_abort_txn (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_close_root (scalar_t__) ; 

__attribute__((used)) static svn_error_t *
abort_edit(void *edit_baton,
           apr_pool_t *pool)
{
  struct edit_baton *eb = edit_baton;
  if ((! eb->txn) || (! eb->txn_owner) || eb->txn_aborted)
    return SVN_NO_ERROR;

  eb->txn_aborted = TRUE;

  /* Since abort_edit is supposed to release resources, do it now. */
  if (eb->txn_root)
    svn_fs_close_root(eb->txn_root);

  return svn_error_trace(svn_fs_abort_txn(eb->txn, pool));
}