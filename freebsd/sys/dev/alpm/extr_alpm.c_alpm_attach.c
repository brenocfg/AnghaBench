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
typedef  int u_int32_t ;
struct alpm_softc {int /*<<< orphan*/ * smbus; int /*<<< orphan*/  lock; int /*<<< orphan*/ * res; int /*<<< orphan*/  smbsh; int /*<<< orphan*/  smbst; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATPC ; 
 int ATPC_SMBCTRL ; 
 int EINVAL ; 
 int ENXIO ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int SMBBA ; 
#define  SMBCLOCK_111K 133 
#define  SMBCLOCK_149K 132 
#define  SMBCLOCK_223K 131 
#define  SMBCLOCK_37K 130 
#define  SMBCLOCK_55K 129 
#define  SMBCLOCK_74K 128 
 int /*<<< orphan*/  SMBHCBC ; 
 int SMBHCBC_CLOCK ; 
 int /*<<< orphan*/  SMBHSI ; 
 int SMBHSI_HOST ; 
 int SMBHSI_SLAVE ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 scalar_t__ alpm_debug ; 
 int /*<<< orphan*/  alpm_detach (int /*<<< orphan*/ ) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct alpm_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
alpm_attach(device_t dev)
{
	int rid;
	u_int32_t l;
	struct alpm_softc *alpm;

	alpm = device_get_softc(dev);

	/* Unlock SMBIO base register access */
	l = pci_read_config(dev, ATPC, 1);
	pci_write_config(dev, ATPC, l & ~ATPC_SMBCTRL, 1);

	/*
	 * XX linux sets clock to 74k, should we?
	l = pci_read_config(dev, SMBHCBC, 1);
	l &= 0x1f;
	l |= SMBCLOCK_74K;
	pci_write_config(dev, SMBHCBC, l, 1);
	 */

	if (bootverbose || alpm_debug) {
		l = pci_read_config(dev, SMBHSI, 1);
		device_printf(dev, "%s/%s",
			(l & SMBHSI_HOST) ? "host":"nohost",
			(l & SMBHSI_SLAVE) ? "slave":"noslave");

		l = pci_read_config(dev, SMBHCBC, 1);
		switch (l & SMBHCBC_CLOCK) {
		case SMBCLOCK_149K:
			printf(" 149K");
			break;
		case SMBCLOCK_74K:
			printf(" 74K");
			break;
		case SMBCLOCK_37K:
			printf(" 37K");
			break;
		case SMBCLOCK_223K:
			printf(" 223K");
			break;
		case SMBCLOCK_111K:
			printf(" 111K");
			break;
		case SMBCLOCK_55K:
			printf(" 55K");
			break;
		default:
			printf("unknown");
			break;
		}
		printf("\n");
	}

	rid = SMBBA;
	alpm->res = bus_alloc_resource_any(dev, SYS_RES_IOPORT, &rid,
	    RF_ACTIVE);

	if (alpm->res == NULL) {
		device_printf(dev,"Could not allocate Bus space\n");
		return (ENXIO);
	}
	alpm->smbst = rman_get_bustag(alpm->res);
	alpm->smbsh = rman_get_bushandle(alpm->res);
	mtx_init(&alpm->lock, device_get_nameunit(dev), "alpm", MTX_DEF);

	/* attach the smbus */
	alpm->smbus = device_add_child(dev, "smbus", -1);
	if (alpm->smbus == NULL) {
		alpm_detach(dev);
		return (EINVAL);
	}
	bus_generic_attach(dev);

	return (0);
}