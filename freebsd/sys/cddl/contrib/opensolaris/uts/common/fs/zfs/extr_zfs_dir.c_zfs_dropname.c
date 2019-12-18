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
struct TYPE_6__ {int /*<<< orphan*/  z_id; TYPE_1__* z_zfsvfs; } ;
typedef  TYPE_2__ znode_t ;
typedef  int /*<<< orphan*/  matchtype_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_5__ {scalar_t__ z_case; int /*<<< orphan*/  z_os; scalar_t__ z_norm; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_MATCH_CASE ; 
 int /*<<< orphan*/  MT_NORMALIZE ; 
 scalar_t__ ZFS_CASE_MIXED ; 
 int zap_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int zap_remove_norm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zfs_dropname(znode_t *dzp, const char *name, znode_t *zp, dmu_tx_t *tx,
    int flag)
{
	int error;

	if (zp->z_zfsvfs->z_norm) {
		matchtype_t mt = MT_NORMALIZE;

		if (zp->z_zfsvfs->z_case == ZFS_CASE_MIXED) {
			mt |= MT_MATCH_CASE;
		}

		error = zap_remove_norm(zp->z_zfsvfs->z_os, dzp->z_id,
		    name, mt, tx);
	} else {
		error = zap_remove(zp->z_zfsvfs->z_os, dzp->z_id, name, tx);
	}

	return (error);
}