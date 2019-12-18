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
struct TYPE_4__ {scalar_t__ dev_handle; int device_info; } ;
struct mptsas_phyinfo {TYPE_2__ attached; } ;
struct mpt_softc {int /*<<< orphan*/  dev; TYPE_1__* sas_portinfo; } ;
struct TYPE_3__ {int num_phys; struct mptsas_phyinfo* phy_info; } ;

/* Variables and functions */
 int MPI_SAS_DEVICE_INFO_SATA_DEVICE ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,char*,int) ; 
 int mpt_enable_sata_wc ; 
 int /*<<< orphan*/  mptsas_set_sata_wc (struct mpt_softc*,TYPE_2__*,int) ; 

__attribute__((used)) static int
mpt_set_initial_config_sas(struct mpt_softc *mpt)
{
	struct mptsas_phyinfo *phyinfo;
	int i;

	if ((mpt_enable_sata_wc != -1) && (mpt->sas_portinfo != NULL)) {
		for (i = 0; i < mpt->sas_portinfo->num_phys; i++) {
			phyinfo = &mpt->sas_portinfo->phy_info[i];
			if (phyinfo->attached.dev_handle == 0)
				continue;
			if ((phyinfo->attached.device_info &
			    MPI_SAS_DEVICE_INFO_SATA_DEVICE) == 0)
				continue;
			if (bootverbose)
				device_printf(mpt->dev,
				    "%sabling SATA WC on phy %d\n",
				    (mpt_enable_sata_wc) ? "En" : "Dis", i);
			mptsas_set_sata_wc(mpt, &phyinfo->attached,
					   mpt_enable_sata_wc);
		}
	}

	return (0);
}