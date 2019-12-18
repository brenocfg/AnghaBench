#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_fs_x__txn_id_t ;
struct TYPE_6__ {scalar_t__ txn_id; int /*<<< orphan*/  pool; struct TYPE_6__* next; } ;
typedef  TYPE_1__ svn_fs_x__shared_txn_data_t ;
struct TYPE_7__ {TYPE_1__* free_txn; TYPE_1__* txns; } ;
typedef  TYPE_2__ svn_fs_x__shared_data_t ;
struct TYPE_8__ {TYPE_2__* shared; } ;
typedef  TYPE_3__ svn_fs_x__data_t ;
struct TYPE_9__ {TYPE_3__* fsap_data; } ;
typedef  TYPE_4__ svn_fs_t ;

/* Variables and functions */
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
free_shared_txn(svn_fs_t *fs, svn_fs_x__txn_id_t txn_id)
{
  svn_fs_x__data_t *ffd = fs->fsap_data;
  svn_fs_x__shared_data_t *ffsd = ffd->shared;
  svn_fs_x__shared_txn_data_t *txn, *prev = NULL;

  for (txn = ffsd->txns; txn; prev = txn, txn = txn->next)
    if (txn->txn_id == txn_id)
      break;

  if (!txn)
    return;

  if (prev)
    prev->next = txn->next;
  else
    ffsd->txns = txn->next;

  /* As we typically will be dealing with one transaction after another,
     we will maintain a single-object free list so that we can hopefully
     keep reusing the same transaction object. */
  if (!ffsd->free_txn)
    ffsd->free_txn = txn;
  else
    svn_pool_destroy(txn->pool);
}