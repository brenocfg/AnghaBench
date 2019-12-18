#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mpt_softc {scalar_t__ do_cfg_role; int cfg_role; int role; } ;
typedef  int /*<<< orphan*/  fc ;
typedef  int U32 ;
struct TYPE_4__ {int Flags; int /*<<< orphan*/  Header; } ;
typedef  TYPE_1__ CONFIG_PAGE_FC_PORT_1 ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MPI_CONFIG_ACTION_PAGE_READ_NVRAM ; 
 int /*<<< orphan*/  MPI_CONFIG_ACTION_PAGE_WRITE_NVRAM ; 
 int /*<<< orphan*/  MPI_CONFIG_PAGETYPE_FC_PORT ; 
 int MPI_FCPORTPAGE1_FLAGS_PROT_FCP_INIT ; 
 int MPI_FCPORTPAGE1_FLAGS_PROT_FCP_TARG ; 
 int MPI_FCPORTPAGE1_FLAGS_PROT_MASK ; 
 int MPI_FCPORTPAGE1_FLAGS_TARGET_MODE_OXID ; 
 int MPT_ROLE_INITIATOR ; 
 int MPT_ROLE_TARGET ; 
 int /*<<< orphan*/  host2mpt_config_page_fc_port_1 (TYPE_1__*) ; 
 int /*<<< orphan*/  mpt2host_config_page_fc_port_1 (TYPE_1__*) ; 
 int mpt_fc_reset_link (struct mpt_softc*,int) ; 
 int /*<<< orphan*/  mpt_prt (struct mpt_softc*,char*) ; 
 int mpt_read_cfg_header (struct mpt_softc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int mpt_read_cfg_page (struct mpt_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 int mpt_write_cfg_page (struct mpt_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
mpt_set_initial_config_fc(struct mpt_softc *mpt)
{
	CONFIG_PAGE_FC_PORT_1 fc;
	U32 fl;
	int r, doit = 0;
	int role;

	r = mpt_read_cfg_header(mpt, MPI_CONFIG_PAGETYPE_FC_PORT, 1, 0,
	    &fc.Header, FALSE, 5000);
	if (r) {
		mpt_prt(mpt, "failed to read FC page 1 header\n");
		return (mpt_fc_reset_link(mpt, 1));
	}

	r = mpt_read_cfg_page(mpt, MPI_CONFIG_ACTION_PAGE_READ_NVRAM, 0,
	    &fc.Header, sizeof (fc), FALSE, 5000);
	if (r) {
		mpt_prt(mpt, "failed to read FC page 1\n");
		return (mpt_fc_reset_link(mpt, 1));
	}
	mpt2host_config_page_fc_port_1(&fc);

	/*
	 * Check our flags to make sure we support the role we want.
	 */
	doit = 0;
	role = 0;
	fl = fc.Flags;

	if (fl & MPI_FCPORTPAGE1_FLAGS_PROT_FCP_INIT) {
		role |= MPT_ROLE_INITIATOR;
	}
	if (fl & MPI_FCPORTPAGE1_FLAGS_PROT_FCP_TARG) {
		role |= MPT_ROLE_TARGET;
	}

	fl &= ~MPI_FCPORTPAGE1_FLAGS_PROT_MASK;

	if (mpt->do_cfg_role == 0) {
		role = mpt->cfg_role;
	} else {
		mpt->do_cfg_role = 0;
	}

	if (role != mpt->cfg_role) {
		if (mpt->cfg_role & MPT_ROLE_INITIATOR) {
			if ((role & MPT_ROLE_INITIATOR) == 0) {
				mpt_prt(mpt, "adding initiator role\n");
				fl |= MPI_FCPORTPAGE1_FLAGS_PROT_FCP_INIT;
				doit++;
			} else {
				mpt_prt(mpt, "keeping initiator role\n");
			}
		} else if (role & MPT_ROLE_INITIATOR) {
			mpt_prt(mpt, "removing initiator role\n");
			doit++;
		}
		if (mpt->cfg_role & MPT_ROLE_TARGET) {
			if ((role & MPT_ROLE_TARGET) == 0) {
				mpt_prt(mpt, "adding target role\n");
				fl |= MPI_FCPORTPAGE1_FLAGS_PROT_FCP_TARG;
				doit++;
			} else {
				mpt_prt(mpt, "keeping target role\n");
			}
		} else if (role & MPT_ROLE_TARGET) {
			mpt_prt(mpt, "removing target role\n");
			doit++;
		}
		mpt->role = mpt->cfg_role;
	}

	if (fl & MPI_FCPORTPAGE1_FLAGS_PROT_FCP_TARG) {
		if ((fl & MPI_FCPORTPAGE1_FLAGS_TARGET_MODE_OXID) == 0) {
			mpt_prt(mpt, "adding OXID option\n");
			fl |= MPI_FCPORTPAGE1_FLAGS_TARGET_MODE_OXID;
			doit++;
		}
	}

	if (doit) {
		fc.Flags = fl;
		host2mpt_config_page_fc_port_1(&fc);
		r = mpt_write_cfg_page(mpt,
		    MPI_CONFIG_ACTION_PAGE_WRITE_NVRAM, 0, &fc.Header,
		    sizeof(fc), FALSE, 5000);
		if (r != 0) {
			mpt_prt(mpt, "failed to update NVRAM with changes\n");
			return (0);
		}
		mpt_prt(mpt, "NOTE: NVRAM changes will not take "
		    "effect until next reboot or IOC reset\n");
	}
	return (0);
}