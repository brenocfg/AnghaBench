#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_6__ {TYPE_3__* priv; } ;
typedef  TYPE_2__ svn_branch__txn_t ;
struct TYPE_7__ {int /*<<< orphan*/  txn; int /*<<< orphan*/  dedit_baton; TYPE_1__* deditor; } ;
typedef  TYPE_3__ svn_branch__txn_priv_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* abort_edit ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_branch__txn_abort (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
compat_branch_txn_abort(svn_branch__txn_t *txn,
                        apr_pool_t *scratch_pool)
{
  svn_branch__txn_priv_t *eb = txn->priv;

  SVN_ERR(eb->deditor->abort_edit(eb->dedit_baton, scratch_pool));

  SVN_ERR(svn_branch__txn_abort(txn->priv->txn,
                                scratch_pool));
  return SVN_NO_ERROR;
}