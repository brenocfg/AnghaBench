#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pid_t ;
struct TYPE_11__ {int /*<<< orphan*/  (* dtms_remove_pid ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ dtrace_mops_t ;
struct TYPE_12__ {int /*<<< orphan*/  dtm_count; int /*<<< orphan*/  dtm_arg; TYPE_1__ dtm_mops; } ;
typedef  TYPE_2__ dtrace_meta_t ;
typedef  int /*<<< orphan*/  dtrace_helper_provdesc_t ;
struct TYPE_13__ {scalar_t__ dofs_offset; } ;
typedef  TYPE_3__ dof_sec_t ;
struct TYPE_14__ {int dofpv_strtab; } ;
typedef  TYPE_4__ dof_provider_t ;
struct TYPE_15__ {scalar_t__ dofhp_dof; } ;
typedef  TYPE_5__ dof_helper_t ;
struct TYPE_16__ {int dofh_secsize; scalar_t__ dofh_secoff; } ;
typedef  TYPE_6__ dof_hdr_t ;

/* Variables and functions */
 int /*<<< orphan*/  dtrace_dofprov2hprov (int /*<<< orphan*/ *,TYPE_4__*,char*) ; 
 TYPE_2__* dtrace_meta_pid ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dtrace_helper_provider_remove_one(dof_helper_t *dhp, dof_sec_t *sec, pid_t pid)
{
	uintptr_t daddr = (uintptr_t)dhp->dofhp_dof;
	dof_hdr_t *dof = (dof_hdr_t *)daddr;
	dof_sec_t *str_sec;
	dof_provider_t *provider;
	char *strtab;
	dtrace_helper_provdesc_t dhpv;
	dtrace_meta_t *meta = dtrace_meta_pid;
	dtrace_mops_t *mops = &meta->dtm_mops;

	provider = (dof_provider_t *)(uintptr_t)(daddr + sec->dofs_offset);
	str_sec = (dof_sec_t *)(uintptr_t)(daddr + dof->dofh_secoff +
	    provider->dofpv_strtab * dof->dofh_secsize);

	strtab = (char *)(uintptr_t)(daddr + str_sec->dofs_offset);

	/*
	 * Create the provider.
	 */
	dtrace_dofprov2hprov(&dhpv, provider, strtab);

	mops->dtms_remove_pid(meta->dtm_arg, &dhpv, pid);

	meta->dtm_count--;
}