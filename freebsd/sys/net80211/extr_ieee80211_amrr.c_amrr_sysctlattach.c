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
struct ieee80211vap {struct ieee80211_amrr* iv_rs; } ;
struct ieee80211_amrr {int /*<<< orphan*/  amrr_min_success_threshold; int /*<<< orphan*/  amrr_max_success_threshold; } ;

/* Variables and functions */
 int CTLFLAG_RW ; 
 int CTLTYPE_INT ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,struct ieee80211vap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_UINT (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 int /*<<< orphan*/  amrr_sysctl_interval ; 

__attribute__((used)) static void
amrr_sysctlattach(struct ieee80211vap *vap,
    struct sysctl_ctx_list *ctx, struct sysctl_oid *tree)
{
	struct ieee80211_amrr *amrr = vap->iv_rs;

	if (!amrr)
		return;

	SYSCTL_ADD_PROC(ctx, SYSCTL_CHILDREN(tree), OID_AUTO,
	    "amrr_rate_interval", CTLTYPE_INT | CTLFLAG_RW, vap,
	    0, amrr_sysctl_interval, "I", "amrr operation interval (ms)");
	/* XXX bounds check values */
	SYSCTL_ADD_UINT(ctx, SYSCTL_CHILDREN(tree), OID_AUTO,
	    "amrr_max_sucess_threshold", CTLFLAG_RW,
	    &amrr->amrr_max_success_threshold, 0, "");
	SYSCTL_ADD_UINT(ctx, SYSCTL_CHILDREN(tree), OID_AUTO,
	    "amrr_min_sucess_threshold", CTLFLAG_RW,
	    &amrr->amrr_min_success_threshold, 0, "");
}