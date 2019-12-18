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
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_4__ {int /*<<< orphan*/  wrapped_txn; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_branch__txn_delete_branch (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
nested_branch_txn_delete_branch(svn_branch__txn_t *txn,
                                const char *bid,
                                apr_pool_t *scratch_pool)
{
  /* Just forwarding: nothing more is needed. */
  SVN_ERR(svn_branch__txn_delete_branch(txn->priv->wrapped_txn,
                                        bid,
                                        scratch_pool));
  return SVN_NO_ERROR;
}