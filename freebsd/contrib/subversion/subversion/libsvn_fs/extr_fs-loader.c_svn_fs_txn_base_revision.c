#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_3__ {int /*<<< orphan*/  base_rev; } ;
typedef  TYPE_1__ svn_fs_txn_t ;

/* Variables and functions */

svn_revnum_t
svn_fs_txn_base_revision(svn_fs_txn_t *txn)
{
  return txn->base_rev;
}