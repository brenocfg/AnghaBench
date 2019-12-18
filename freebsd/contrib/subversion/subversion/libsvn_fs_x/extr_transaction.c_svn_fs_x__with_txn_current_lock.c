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
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  create_lock_baton (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ * (*) (void*,int /*<<< orphan*/ *),void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txn_lock ; 
 int /*<<< orphan*/  with_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_x__with_txn_current_lock(svn_fs_t *fs,
                                svn_error_t *(*body)(void *baton,
                                                     apr_pool_t *scratch_pool),
                                void *baton,
                                apr_pool_t *scratch_pool)
{
  return svn_error_trace(
           with_lock(create_lock_baton(fs, txn_lock, body, baton,
                                       scratch_pool),
                     scratch_pool));
}