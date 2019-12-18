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
struct TYPE_6__ {int /*<<< orphan*/  proplist; } ;
typedef  TYPE_1__ transaction_t ;
struct TYPE_7__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  fs; } ;
typedef  TYPE_2__ trail_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct revision_proplist_args {int /*<<< orphan*/ * table_p; int /*<<< orphan*/  rev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  get_rev_txn (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
txn_body_revision_proplist(void *baton, trail_t *trail)
{
  struct revision_proplist_args *args = baton;
  transaction_t *txn;

  SVN_ERR(get_rev_txn(&txn, NULL, trail->fs, args->rev, trail, trail->pool));
  *(args->table_p) = txn->proplist;
  return SVN_NO_ERROR;
}