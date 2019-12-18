#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sysctl_oid {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct mpt_softc {int /*<<< orphan*/  raid_nonopt_volumes; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int CTLFLAG_RW ; 
 int CTLTYPE_INT ; 
 int CTLTYPE_STRING ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,struct mpt_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_UINT (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 struct sysctl_oid* device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_raid_sysctl_vol_member_wce ; 
 int /*<<< orphan*/  mpt_raid_sysctl_vol_queue_depth ; 
 int /*<<< orphan*/  mpt_raid_sysctl_vol_resync_rate ; 

__attribute__((used)) static void
mpt_raid_sysctl_attach(struct mpt_softc *mpt)
{
	struct sysctl_ctx_list *ctx = device_get_sysctl_ctx(mpt->dev);
	struct sysctl_oid *tree = device_get_sysctl_tree(mpt->dev);

	SYSCTL_ADD_PROC(ctx, SYSCTL_CHILDREN(tree), OID_AUTO,
			"vol_member_wce", CTLTYPE_STRING | CTLFLAG_RW, mpt, 0,
			mpt_raid_sysctl_vol_member_wce, "A",
			"volume member WCE(On,Off,On-During-Rebuild,NC)");

	SYSCTL_ADD_PROC(ctx, SYSCTL_CHILDREN(tree), OID_AUTO,
			"vol_queue_depth", CTLTYPE_INT | CTLFLAG_RW, mpt, 0,
			mpt_raid_sysctl_vol_queue_depth, "I",
			"default volume queue depth");

	SYSCTL_ADD_PROC(ctx, SYSCTL_CHILDREN(tree), OID_AUTO,
			"vol_resync_rate", CTLTYPE_INT | CTLFLAG_RW, mpt, 0,
			mpt_raid_sysctl_vol_resync_rate, "I",
			"volume resync priority (0 == NC, 1 - 255)");
	SYSCTL_ADD_UINT(ctx, SYSCTL_CHILDREN(tree), OID_AUTO,
			"nonoptimal_volumes", CTLFLAG_RD,
			&mpt->raid_nonopt_volumes, 0,
			"number of nonoptimal volumes");
}