#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_6__ {int PortSettings; } ;
struct TYPE_8__ {int Configuration; int /*<<< orphan*/  Header; } ;
struct mpt_softc {int mpt_disc_enable; int mpt_ini_id; TYPE_2__* mpt_dev_page1; TYPE_1__ mpt_port_page2; TYPE_3__ mpt_port_page1; scalar_t__ mpt_tag_enable; } ;
struct TYPE_7__ {scalar_t__ Configuration; scalar_t__ RequestedParameters; } ;
typedef  TYPE_3__ CONFIG_PAGE_SCSI_PORT_1 ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int MPI_SCSIPORTPAGE1_CFG_SHIFT_PORT_RESPONSE_ID ; 
 int MPI_SCSIPORTPAGE2_PORT_ALL_MASTER_SETTINGS ; 
 int MPI_SCSIPORTPAGE2_PORT_MASK_NEGO_MASTER_SETTINGS ; 
 int /*<<< orphan*/  MPT_PRT_NEGOTIATION ; 
 int /*<<< orphan*/  host2mpt_config_page_scsi_port_1 (TYPE_3__*) ; 
 int /*<<< orphan*/  mpt2host_config_page_scsi_port_1 (TYPE_3__*) ; 
 int /*<<< orphan*/  mpt_lprt (struct mpt_softc*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mpt_prt (struct mpt_softc*,char*,...) ; 
 int mpt_read_cur_cfg_page (struct mpt_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mpt_update_spi_config (struct mpt_softc*,int) ; 
 int mpt_write_cur_cfg_page (struct mpt_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
mpt_set_initial_config_spi(struct mpt_softc *mpt)
{
	int error, i, pp1val;

	mpt->mpt_disc_enable = 0xff;
	mpt->mpt_tag_enable = 0;

	pp1val = ((1 << mpt->mpt_ini_id) <<
	    MPI_SCSIPORTPAGE1_CFG_SHIFT_PORT_RESPONSE_ID) | mpt->mpt_ini_id;
	if (mpt->mpt_port_page1.Configuration != pp1val) {
		CONFIG_PAGE_SCSI_PORT_1 tmp;

		mpt_prt(mpt, "SPI Port Page 1 Config value bad (%x)- should "
		    "be %x\n", mpt->mpt_port_page1.Configuration, pp1val);
		tmp = mpt->mpt_port_page1;
		tmp.Configuration = pp1val;
		host2mpt_config_page_scsi_port_1(&tmp);
		error = mpt_write_cur_cfg_page(mpt, 0,
		    &tmp.Header, sizeof(tmp), FALSE, 5000);
		if (error) {
			return (-1);
		}
		error = mpt_read_cur_cfg_page(mpt, 0,
		    &tmp.Header, sizeof(tmp), FALSE, 5000);
		if (error) {
			return (-1);
		}
		mpt2host_config_page_scsi_port_1(&tmp);
		if (tmp.Configuration != pp1val) {
			mpt_prt(mpt,
			    "failed to reset SPI Port Page 1 Config value\n");
			return (-1);
		}
		mpt->mpt_port_page1 = tmp;
	}

	/*
	 * The purpose of this exercise is to get
	 * all targets back to async/narrow.
	 *
	 * We skip this step if the BIOS has already negotiated
	 * speeds with the targets.
	 */
	i = mpt->mpt_port_page2.PortSettings &
	    MPI_SCSIPORTPAGE2_PORT_MASK_NEGO_MASTER_SETTINGS;
	if (i == MPI_SCSIPORTPAGE2_PORT_ALL_MASTER_SETTINGS) {
		mpt_lprt(mpt, MPT_PRT_NEGOTIATION,
		    "honoring BIOS transfer negotiations\n");
	} else {
		for (i = 0; i < 16; i++) {
			mpt->mpt_dev_page1[i].RequestedParameters = 0;
			mpt->mpt_dev_page1[i].Configuration = 0;
			(void) mpt_update_spi_config(mpt, i);
		}
	}
	return (0);
}