#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_fs_id_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_3__ {int /*<<< orphan*/  txn_id; } ;
struct TYPE_4__ {TYPE_1__ private_id; } ;
typedef  TYPE_2__ fs_fs__id_t ;

/* Variables and functions */
 int /*<<< orphan*/  svn_fs_fs__id_txn_used (int /*<<< orphan*/ *) ; 

svn_boolean_t
svn_fs_fs__id_is_txn(const svn_fs_id_t *fs_id)
{
  const fs_fs__id_t *id = (const fs_fs__id_t *)fs_id;

  return svn_fs_fs__id_txn_used(&id->private_id.txn_id);
}