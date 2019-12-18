#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ kind; int /*<<< orphan*/  proplist; } ;
typedef  TYPE_1__ transaction_t ;
struct TYPE_7__ {int /*<<< orphan*/  fs; int /*<<< orphan*/  pool; } ;
typedef  TYPE_2__ trail_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct txn_proplist_args {int /*<<< orphan*/ * table_p; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  get_txn (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_fs_base__err_txn_not_mutable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ transaction_kind_normal ; 

__attribute__((used)) static svn_error_t *
txn_body_txn_proplist(void *baton, trail_t *trail)
{
  transaction_t *txn;
  struct txn_proplist_args *args = baton;

  SVN_ERR(get_txn(&txn, trail->fs, args->id, FALSE, trail, trail->pool));
  if (txn->kind != transaction_kind_normal)
    return svn_fs_base__err_txn_not_mutable(trail->fs, args->id);

  *(args->table_p) = txn->proplist;
  return SVN_NO_ERROR;
}