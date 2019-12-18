#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_7__ {TYPE_3__* priv; } ;
typedef  TYPE_2__ svn_branch__txn_t ;
struct TYPE_8__ {int /*<<< orphan*/  txn; int /*<<< orphan*/  dedit_baton; TYPE_1__* deditor; } ;
typedef  TYPE_3__ svn_branch__txn_priv_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* abort_edit ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* close_edit ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * drive_changes (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_branch__txn_complete (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_branch__txn_finalize_eids (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_branch__txn_sequence_point (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_compose_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
compat_branch_txn_complete(svn_branch__txn_t *txn,
                           apr_pool_t *scratch_pool)
{
  svn_branch__txn_priv_t *eb = txn->priv;
  svn_error_t *err;

  /* Convert the transaction to a revision */
  SVN_ERR(svn_branch__txn_sequence_point(txn->priv->txn, scratch_pool));
  SVN_ERR(svn_branch__txn_finalize_eids(txn->priv->txn, scratch_pool));

  err = drive_changes(eb, scratch_pool);

  if (!err)
     {
       err = svn_error_compose_create(err, eb->deditor->close_edit(
                                                            eb->dedit_baton,
                                                            scratch_pool));
     }

  if (err)
    svn_error_clear(eb->deditor->abort_edit(eb->dedit_baton, scratch_pool));

  SVN_ERR(svn_branch__txn_complete(txn->priv->txn, scratch_pool));

  return err;
}