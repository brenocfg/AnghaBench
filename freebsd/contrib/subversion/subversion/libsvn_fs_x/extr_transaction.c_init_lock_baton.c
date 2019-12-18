#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {void* is_global_lock; int /*<<< orphan*/  lock_pool; TYPE_4__* fs; int /*<<< orphan*/  lock_path; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ with_lock_baton_t ;
struct TYPE_9__ {int /*<<< orphan*/  fs_pack_lock; int /*<<< orphan*/  fs_write_lock; int /*<<< orphan*/  txn_current_lock; } ;
typedef  TYPE_2__ svn_fs_x__shared_data_t ;
struct TYPE_10__ {TYPE_2__* shared; } ;
typedef  TYPE_3__ svn_fs_x__data_t ;
typedef  int lock_id_t ;
struct TYPE_11__ {TYPE_3__* fsap_data; } ;

/* Variables and functions */
 void* FALSE ; 
 void* TRUE ; 
#define  pack_lock 130 
 int /*<<< orphan*/  svn_fs_x__path_lock (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__path_pack_lock (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__path_txn_current_lock (TYPE_4__*,int /*<<< orphan*/ ) ; 
#define  txn_lock 129 
#define  write_lock 128 

__attribute__((used)) static void
init_lock_baton(with_lock_baton_t *baton,
                lock_id_t lock_id)
{
  svn_fs_x__data_t *ffd = baton->fs->fsap_data;
  svn_fs_x__shared_data_t *ffsd = ffd->shared;

  switch (lock_id)
    {
    case txn_lock:
      baton->mutex = ffsd->txn_current_lock;
      baton->lock_path = svn_fs_x__path_txn_current_lock(baton->fs,
                                                         baton->lock_pool);
      baton->is_global_lock = FALSE;
      break;

    case write_lock:
      baton->mutex = ffsd->fs_write_lock;
      baton->lock_path = svn_fs_x__path_lock(baton->fs, baton->lock_pool);
      baton->is_global_lock = TRUE;
      break;

    case pack_lock:
      baton->mutex = ffsd->fs_pack_lock;
      baton->lock_path = svn_fs_x__path_pack_lock(baton->fs,
                                                  baton->lock_pool);
      baton->is_global_lock = FALSE;
      break;
    }
}