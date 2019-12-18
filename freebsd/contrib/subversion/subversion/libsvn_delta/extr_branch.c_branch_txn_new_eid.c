#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_5__ {TYPE_1__* priv; } ;
typedef  TYPE_2__ svn_branch__txn_t ;
typedef  int svn_branch__eid_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_4__ {int first_eid; } ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 

__attribute__((used)) static svn_error_t *
branch_txn_new_eid(svn_branch__txn_t *txn,
                   svn_branch__eid_t *eid_p,
                   apr_pool_t *scratch_pool)
{
  int eid = (txn->priv->first_eid < 0) ? txn->priv->first_eid - 1 : -2;

  txn->priv->first_eid = eid;
  if (eid_p)
    *eid_p = eid;
  return SVN_NO_ERROR;
}