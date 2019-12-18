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
struct TYPE_8__ {TYPE_4__* fsap_data; } ;
typedef  TYPE_1__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_fs__id_part_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_9__ {struct TYPE_9__* next; int /*<<< orphan*/  being_written; int /*<<< orphan*/  txn_id; int /*<<< orphan*/ * pool; } ;
typedef  TYPE_2__ fs_fs_shared_txn_data_t ;
struct TYPE_10__ {TYPE_2__* txns; int /*<<< orphan*/  common_pool; TYPE_2__* free_txn; } ;
typedef  TYPE_3__ fs_fs_shared_data_t ;
struct TYPE_11__ {TYPE_3__* shared; } ;
typedef  TYPE_4__ fs_fs_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 TYPE_2__* apr_palloc (int /*<<< orphan*/ *,int) ; 
 scalar_t__ svn_fs_fs__id_part_eq (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ ) ; 

__attribute__((used)) static fs_fs_shared_txn_data_t *
get_shared_txn(svn_fs_t *fs,
               const svn_fs_fs__id_part_t *txn_id,
               svn_boolean_t create_new)
{
  fs_fs_data_t *ffd = fs->fsap_data;
  fs_fs_shared_data_t *ffsd = ffd->shared;
  fs_fs_shared_txn_data_t *txn;

  for (txn = ffsd->txns; txn; txn = txn->next)
    if (svn_fs_fs__id_part_eq(&txn->txn_id, txn_id))
      break;

  if (txn || !create_new)
    return txn;

  /* Use the transaction object from the (single-object) freelist,
     if one is available, or otherwise create a new object. */
  if (ffsd->free_txn)
    {
      txn = ffsd->free_txn;
      ffsd->free_txn = NULL;
    }
  else
    {
      apr_pool_t *subpool = svn_pool_create(ffsd->common_pool);
      txn = apr_palloc(subpool, sizeof(*txn));
      txn->pool = subpool;
    }

  txn->txn_id = *txn_id;
  txn->being_written = FALSE;

  /* Link this transaction into the head of the list.  We will typically
     be dealing with only one active transaction at a time, so it makes
     sense for searches through the transaction list to look at the
     newest transactions first.  */
  txn->next = ffsd->txns;
  ffsd->txns = txn;

  return txn;
}