#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint32_t ;
struct ichwd_device {int tco_version; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ driver_t ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/ * BUS_ADD_CHILD (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ICH_GCS_OFFSET ; 
 int /*<<< orphan*/  ICH_GCS_SIZE ; 
 int /*<<< orphan*/  ICH_PBASE ; 
 int ICH_PMC_OFFSET ; 
 int /*<<< orphan*/  ICH_PMC_SIZE ; 
 int /*<<< orphan*/  ICH_RCBA ; 
 int /*<<< orphan*/  ICH_TCOBASE ; 
 int ICH_TCOBASE_ADDRMASK ; 
 int /*<<< orphan*/  ICH_TCOBASE_SIZE ; 
 int /*<<< orphan*/  ICH_TCOCTL ; 
 int ICH_TCOCTL_TCO_BASE_EN ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int PCR_REG_OFF (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SBREG_BAR ; 
 int /*<<< orphan*/  SMB_GC_REG ; 
 int /*<<< orphan*/  SMB_GC_SIZE ; 
 int /*<<< orphan*/  SMB_PORT_ID ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int bus_set_resource (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * device_find_child (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ichwd_find_ich_lpc_bridge (int /*<<< orphan*/ *,struct ichwd_device**) ; 
 int /*<<< orphan*/ * ichwd_find_smb_dev (int /*<<< orphan*/ *,struct ichwd_device**) ; 
 int /*<<< orphan*/  ichwd_verbose_printf (int /*<<< orphan*/ *,char*,int,...) ; 
 int pci_cfgregread (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_cfgregwrite (int /*<<< orphan*/ ,int,int,int,int,int) ; 
 int pci_read_config (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ichwd_identify(driver_t *driver, device_t parent)
{
	struct ichwd_device *id_p;
	device_t ich, smb;
	device_t dev;
	uint64_t base_address64;
	uint32_t base_address;
	uint32_t ctl;
	int rc;

	ich = ichwd_find_ich_lpc_bridge(parent, &id_p);
	if (ich == NULL) {
		smb = ichwd_find_smb_dev(parent, &id_p);
		if (smb == NULL)
			return;
	}

	KASSERT(id_p->tco_version >= 1,
	    ("unexpected TCO version %d", id_p->tco_version));
	KASSERT(id_p->tco_version != 4 || smb != NULL,
	    ("could not find PCI SMBus device for TCOv4"));
	KASSERT(id_p->tco_version >= 4 || ich != NULL,
	    ("could not find PCI LPC bridge device for TCOv1-3"));

	/* good, add child to bus */
	if ((dev = device_find_child(parent, driver->name, 0)) == NULL)
		dev = BUS_ADD_CHILD(parent, 0, driver->name, 0);

	if (dev == NULL)
		return;

	switch (id_p->tco_version) {
	case 1:
		break;
	case 2:
		/* get RCBA (root complex base address) */
		base_address = pci_read_config(ich, ICH_RCBA, 4);
		rc = bus_set_resource(ich, SYS_RES_MEMORY, 0,
		    (base_address & 0xffffc000) + ICH_GCS_OFFSET,
		    ICH_GCS_SIZE);
		if (rc)
			ichwd_verbose_printf(dev,
			    "Can not set TCO v%d memory resource for RCBA\n",
			    id_p->tco_version);
		break;
	case 3:
		/* get PBASE (Power Management Controller base address) */
		base_address = pci_read_config(ich, ICH_PBASE, 4);
		rc = bus_set_resource(ich, SYS_RES_MEMORY, 0,
		    (base_address & 0xfffffe00) + ICH_PMC_OFFSET,
		    ICH_PMC_SIZE);
		if (rc)
			ichwd_verbose_printf(dev,
			    "Can not set TCO v%d memory resource for PBASE\n",
			    id_p->tco_version);
		break;
	case 4:
		/* Get TCO base address. */
		ctl = pci_read_config(smb, ICH_TCOCTL, 4);
		if ((ctl & ICH_TCOCTL_TCO_BASE_EN) == 0) {
			ichwd_verbose_printf(dev,
			    "TCO v%d decoding is not enabled\n",
			    id_p->tco_version);
			break;
		}
		base_address = pci_read_config(smb, ICH_TCOBASE, 4);
		rc = bus_set_resource(dev, SYS_RES_IOPORT, 0,
		    base_address & ICH_TCOBASE_ADDRMASK, ICH_TCOBASE_SIZE);
		if (rc != 0) {
			ichwd_verbose_printf(dev,
			    "Can not set TCO v%d I/O resource (err = %d)\n",
			    id_p->tco_version, rc);
		}

		/*
		 * Unhide Primary to Sideband Bridge (P2SB) PCI device, so that
		 * we can discover the base address of Private Configuration
		 * Space via the bridge's BAR.
		 * Then hide back the bridge.
		 */
		pci_cfgregwrite(0, 31, 1, 0xe1, 0, 1);
		base_address64 = pci_cfgregread(0, 31, 1, SBREG_BAR + 4, 4);
		base_address64 <<= 32;
		base_address64 |= pci_cfgregread(0, 31, 1, SBREG_BAR, 4);
		base_address64 &= ~0xfull;
		pci_cfgregwrite(0, 31, 1, 0xe1, 1, 1);

		/*
		 * No Reboot bit is in General Control register, offset 0xc,
		 * within the SMBus target port, ID 0xc6.
		 */
		base_address64 += PCR_REG_OFF(SMB_PORT_ID, SMB_GC_REG);
		rc = bus_set_resource(dev, SYS_RES_MEMORY, 1, base_address64,
		    SMB_GC_SIZE);
		if (rc != 0) {
			ichwd_verbose_printf(dev,
			    "Can not set TCO v%d PCR I/O resource (err = %d)\n",
			    id_p->tco_version, rc);
		}

		break;
	default:
		ichwd_verbose_printf(dev,
		    "Can not set unknown TCO v%d memory resource for unknown base address\n",
		    id_p->tco_version);
		break;
	}
}