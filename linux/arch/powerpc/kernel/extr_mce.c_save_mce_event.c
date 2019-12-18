#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct pt_regs {int msr; int /*<<< orphan*/ * gpr; } ;
struct mce_error_info {int /*<<< orphan*/  ignore_event; int /*<<< orphan*/  error_class; int /*<<< orphan*/  sync_error; int /*<<< orphan*/  severity; int /*<<< orphan*/  initiator; } ;
struct TYPE_16__ {int effective_address_provided; int physical_address_provided; int /*<<< orphan*/  ignore_event; scalar_t__ physical_address; scalar_t__ effective_address; } ;
struct TYPE_15__ {int effective_address_provided; scalar_t__ effective_address; } ;
struct TYPE_14__ {int effective_address_provided; scalar_t__ effective_address; } ;
struct TYPE_13__ {int effective_address_provided; scalar_t__ effective_address; } ;
struct TYPE_12__ {int effective_address_provided; scalar_t__ effective_address; } ;
struct TYPE_11__ {int effective_address_provided; scalar_t__ effective_address; } ;
struct TYPE_10__ {int effective_address_provided; scalar_t__ effective_address; } ;
struct TYPE_17__ {TYPE_7__ ue_error; TYPE_6__ link_error; TYPE_5__ ra_error; TYPE_4__ user_error; TYPE_3__ erat_error; TYPE_2__ slb_error; TYPE_1__ tlb_error; } ;
struct machine_check_event {int srr1; int in_use; scalar_t__ error_type; TYPE_8__ u; int /*<<< orphan*/  error_class; int /*<<< orphan*/  sync_error; int /*<<< orphan*/  severity; int /*<<< orphan*/  initiator; int /*<<< orphan*/  disposition; int /*<<< orphan*/  cpu; int /*<<< orphan*/  gpr3; scalar_t__ srr0; int /*<<< orphan*/  version; } ;
struct TYPE_18__ {int /*<<< orphan*/  paca_index; } ;

/* Variables and functions */
 int MAX_MC_EVT ; 
 int /*<<< orphan*/  MCE_DISPOSITION_NOT_RECOVERED ; 
 int /*<<< orphan*/  MCE_DISPOSITION_RECOVERED ; 
 scalar_t__ MCE_ERROR_TYPE_ERAT ; 
 scalar_t__ MCE_ERROR_TYPE_LINK ; 
 scalar_t__ MCE_ERROR_TYPE_RA ; 
 scalar_t__ MCE_ERROR_TYPE_SLB ; 
 scalar_t__ MCE_ERROR_TYPE_TLB ; 
 scalar_t__ MCE_ERROR_TYPE_UE ; 
 scalar_t__ MCE_ERROR_TYPE_USER ; 
 int /*<<< orphan*/  MCE_V1 ; 
 int MSR_RI ; 
 scalar_t__ ULONG_MAX ; 
 int __this_cpu_inc_return (int /*<<< orphan*/ ) ; 
 TYPE_9__* get_paca () ; 
 int /*<<< orphan*/  machine_check_ue_event (struct machine_check_event*) ; 
 int /*<<< orphan*/ * mce_event ; 
 int /*<<< orphan*/  mce_nest_count ; 
 int /*<<< orphan*/  mce_set_error_info (struct machine_check_event*,struct mce_error_info*) ; 
 struct machine_check_event* this_cpu_ptr (int /*<<< orphan*/ *) ; 

void save_mce_event(struct pt_regs *regs, long handled,
		    struct mce_error_info *mce_err,
		    uint64_t nip, uint64_t addr, uint64_t phys_addr)
{
	int index = __this_cpu_inc_return(mce_nest_count) - 1;
	struct machine_check_event *mce = this_cpu_ptr(&mce_event[index]);

	/*
	 * Return if we don't have enough space to log mce event.
	 * mce_nest_count may go beyond MAX_MC_EVT but that's ok,
	 * the check below will stop buffer overrun.
	 */
	if (index >= MAX_MC_EVT)
		return;

	/* Populate generic machine check info */
	mce->version = MCE_V1;
	mce->srr0 = nip;
	mce->srr1 = regs->msr;
	mce->gpr3 = regs->gpr[3];
	mce->in_use = 1;
	mce->cpu = get_paca()->paca_index;

	/* Mark it recovered if we have handled it and MSR(RI=1). */
	if (handled && (regs->msr & MSR_RI))
		mce->disposition = MCE_DISPOSITION_RECOVERED;
	else
		mce->disposition = MCE_DISPOSITION_NOT_RECOVERED;

	mce->initiator = mce_err->initiator;
	mce->severity = mce_err->severity;
	mce->sync_error = mce_err->sync_error;
	mce->error_class = mce_err->error_class;

	/*
	 * Populate the mce error_type and type-specific error_type.
	 */
	mce_set_error_info(mce, mce_err);

	if (!addr)
		return;

	if (mce->error_type == MCE_ERROR_TYPE_TLB) {
		mce->u.tlb_error.effective_address_provided = true;
		mce->u.tlb_error.effective_address = addr;
	} else if (mce->error_type == MCE_ERROR_TYPE_SLB) {
		mce->u.slb_error.effective_address_provided = true;
		mce->u.slb_error.effective_address = addr;
	} else if (mce->error_type == MCE_ERROR_TYPE_ERAT) {
		mce->u.erat_error.effective_address_provided = true;
		mce->u.erat_error.effective_address = addr;
	} else if (mce->error_type == MCE_ERROR_TYPE_USER) {
		mce->u.user_error.effective_address_provided = true;
		mce->u.user_error.effective_address = addr;
	} else if (mce->error_type == MCE_ERROR_TYPE_RA) {
		mce->u.ra_error.effective_address_provided = true;
		mce->u.ra_error.effective_address = addr;
	} else if (mce->error_type == MCE_ERROR_TYPE_LINK) {
		mce->u.link_error.effective_address_provided = true;
		mce->u.link_error.effective_address = addr;
	} else if (mce->error_type == MCE_ERROR_TYPE_UE) {
		mce->u.ue_error.effective_address_provided = true;
		mce->u.ue_error.effective_address = addr;
		if (phys_addr != ULONG_MAX) {
			mce->u.ue_error.physical_address_provided = true;
			mce->u.ue_error.physical_address = phys_addr;
			mce->u.ue_error.ignore_event = mce_err->ignore_event;
			machine_check_ue_event(mce);
		}
	}
	return;
}