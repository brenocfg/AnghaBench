#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  zl_os; int /*<<< orphan*/  zl_replaying_seq; } ;
typedef  TYPE_1__ zilog_t ;
typedef  int /*<<< orphan*/  u_longlong_t ;
struct TYPE_6__ {int lrc_txtype; scalar_t__ lrc_seq; } ;
typedef  TYPE_2__ lr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CE_WARN ; 
 int TX_CI ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 int /*<<< orphan*/  cmn_err (int /*<<< orphan*/ ,char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dmu_objset_name (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
zil_replay_error(zilog_t *zilog, lr_t *lr, int error)
{
	char name[ZFS_MAX_DATASET_NAME_LEN];

	zilog->zl_replaying_seq--;	/* didn't actually replay this one */

	dmu_objset_name(zilog->zl_os, name);

	cmn_err(CE_WARN, "ZFS replay transaction error %d, "
	    "dataset %s, seq 0x%llx, txtype %llu %s\n", error, name,
	    (u_longlong_t)lr->lrc_seq,
	    (u_longlong_t)(lr->lrc_txtype & ~TX_CI),
	    (lr->lrc_txtype & TX_CI) ? "CI" : "");

	return (error);
}