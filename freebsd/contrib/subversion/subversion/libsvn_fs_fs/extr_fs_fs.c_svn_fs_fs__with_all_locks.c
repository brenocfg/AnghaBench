#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  with_lock_baton_t ;
struct TYPE_5__ {TYPE_2__* fsap_data; } ;
typedef  TYPE_1__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_6__ {scalar_t__ format; } ;
typedef  TYPE_2__ fs_fs_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ SVN_FS_FS__MIN_PACK_LOCK_FORMAT ; 
 scalar_t__ SVN_FS_FS__MIN_TXN_CURRENT_FORMAT ; 
 int /*<<< orphan*/ * chain_lock_baton (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * create_lock_baton (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ * (*) (void*,int /*<<< orphan*/ *),void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pack_lock ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txn_lock ; 
 int /*<<< orphan*/  with_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock ; 

svn_error_t *
svn_fs_fs__with_all_locks(svn_fs_t *fs,
                          svn_error_t *(*body)(void *baton,
                                               apr_pool_t *pool),
                          void *baton,
                          apr_pool_t *pool)
{
  fs_fs_data_t *ffd = fs->fsap_data;

  /* Be sure to use the correct lock ordering as documented in
     fs_fs_shared_data_t.  The lock chain is being created in
     innermost (last to acquire) -> outermost (first to acquire) order. */
  with_lock_baton_t *lock_baton
    = create_lock_baton(fs, write_lock, body, baton, pool);

  if (ffd->format >= SVN_FS_FS__MIN_PACK_LOCK_FORMAT)
    lock_baton = chain_lock_baton(pack_lock, lock_baton);

  if (ffd->format >= SVN_FS_FS__MIN_TXN_CURRENT_FORMAT)
    lock_baton = chain_lock_baton(txn_lock, lock_baton);

  return svn_error_trace(with_lock(lock_baton, pool));
}