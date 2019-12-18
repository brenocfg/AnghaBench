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
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_3__ {int /*<<< orphan*/  txn_id; } ;
typedef  TYPE_1__ representation_t ;

/* Variables and functions */
 int /*<<< orphan*/  svn_fs_fs__id_txn_used (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_boolean_t
is_txn_rep(const representation_t *rep)
{
  return svn_fs_fs__id_txn_used(&rep->txn_id);
}