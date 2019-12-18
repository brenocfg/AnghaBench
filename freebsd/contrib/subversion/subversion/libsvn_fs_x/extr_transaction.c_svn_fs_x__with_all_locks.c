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
typedef  int /*<<< orphan*/  with_lock_baton_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * chain_lock_baton (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * create_lock_baton (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ * (*) (void*,int /*<<< orphan*/ *),void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pack_lock ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txn_lock ; 
 int /*<<< orphan*/  with_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock ; 

svn_error_t *
svn_fs_x__with_all_locks(svn_fs_t *fs,
                         svn_error_t *(*body)(void *baton,
                                              apr_pool_t *scratch_pool),
                         void *baton,
                         apr_pool_t *scratch_pool)
{
  /* Be sure to use the correct lock ordering as documented in
     fs_fs_shared_data_t.  The lock chain is being created in
     innermost (last to acquire) -> outermost (first to acquire) order. */
  with_lock_baton_t *lock_baton
    = create_lock_baton(fs, txn_lock, body, baton, scratch_pool);

  lock_baton = chain_lock_baton(write_lock, lock_baton);
  lock_baton = chain_lock_baton(pack_lock, lock_baton);

  return svn_error_trace(with_lock(lock_baton, scratch_pool));
}