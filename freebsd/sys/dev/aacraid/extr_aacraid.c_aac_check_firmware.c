#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
typedef  scalar_t__ time_t ;
struct TYPE_2__ {scalar_t__ aif_send_command; } ;
struct aac_softc {int flags; int supported_options; int doorbell_mask; int hint_flags; int aac_max_fibs; int aac_max_fib_size; int aac_max_sectors; int aac_max_aif; int aac_sg_tablesize; scalar_t__ aac_hwif; int aac_max_msix; int aac_max_fibs_alloc; int /*<<< orphan*/  aac_dev; int /*<<< orphan*/ * aac_regs_res0; int /*<<< orphan*/  aac_bhandle0; int /*<<< orphan*/  aac_btag0; int /*<<< orphan*/  aac_regs_rid0; TYPE_1__ aac_if; } ;
struct aac_sg_entry64 {int dummy; } ;
struct aac_sg_entry {int dummy; } ;
struct aac_fib_xporthdr {int dummy; } ;
struct aac_fib {int dummy; } ;
struct aac_blockwrite64 {int dummy; } ;
struct aac_blockwrite {int dummy; } ;
typedef  int /*<<< orphan*/  bus_addr_t ;

/* Variables and functions */
 scalar_t__ AAC_BOOT_TIMEOUT ; 
 int AAC_FIB_DATASIZE ; 
 int AAC_FLAGS_256FIBS ; 
 int AAC_FLAGS_4GB_WINDOW ; 
 int AAC_FLAGS_ARRAY_64BIT ; 
 int AAC_FLAGS_ENABLE_CAM ; 
 int AAC_FLAGS_LBA_64BIT ; 
 int AAC_FLAGS_NEW_COMM ; 
 int AAC_FLAGS_NEW_COMM_TYPE1 ; 
 int AAC_FLAGS_NEW_COMM_TYPE2 ; 
 int AAC_FLAGS_NEW_COMM_TYPE34 ; 
 int AAC_FLAGS_NO4GB ; 
 int AAC_FLAGS_PERC2QC ; 
 int AAC_FLAGS_RAW_IO ; 
 int AAC_FLAGS_SG_64BIT ; 
 int AAC_FLAGS_SYNC_MODE ; 
 int AAC_FLASH_UPD_FAILED ; 
 int AAC_FLASH_UPD_PENDING ; 
 int AAC_FLASH_UPD_SUCCESS ; 
 scalar_t__ AAC_FWUPD_TIMEOUT ; 
 int AAC_GET_FWSTATUS (struct aac_softc*) ; 
 int AAC_GET_MAILBOX (struct aac_softc*,int) ; 
 scalar_t__ AAC_HWIF_SRCV ; 
 int /*<<< orphan*/  AAC_MONKER_GETCOMMPREF ; 
 int /*<<< orphan*/  AAC_MONKER_GETINFO ; 
 int /*<<< orphan*/  AAC_MONKER_GETKERNVER ; 
 int AAC_SRB_STS_INVALID_REQUEST ; 
 int AAC_SUPPORTED_4GB_WINDOW ; 
 int AAC_SUPPORTED_64BIT_ARRAYSIZE ; 
 int AAC_SUPPORTED_NEW_COMM_TYPE1 ; 
 int AAC_SUPPORTED_NEW_COMM_TYPE2 ; 
 int AAC_SUPPORTED_NEW_COMM_TYPE3 ; 
 int AAC_SUPPORTED_NEW_COMM_TYPE4 ; 
 int AAC_SUPPORTED_NONDASD ; 
 int AAC_SUPPORTED_SGMAP_HOST64 ; 
 int AAC_UP_AND_RUNNING ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int EINVAL ; 
 int EIO ; 
 int ENXIO ; 
 char* HBA_FLAGS_DBG_FUNCTION_ENTRY_B ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  aacraid_get_fw_debug_buffer (struct aac_softc*) ; 
 scalar_t__ aacraid_sync_command (struct aac_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bus_alloc_resource_anywhere (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fwprintf (struct aac_softc*,char*,char*) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 
 int rman_get_size (int /*<<< orphan*/ *) ; 
 scalar_t__ time_uptime ; 

__attribute__((used)) static int
aac_check_firmware(struct aac_softc *sc)
{
	u_int32_t code, major, minor, maxsize;
	u_int32_t options = 0, atu_size = 0, status, waitCount;
	time_t then;

	fwprintf(sc, HBA_FLAGS_DBG_FUNCTION_ENTRY_B, "");

	/* check if flash update is running */
	if (AAC_GET_FWSTATUS(sc) & AAC_FLASH_UPD_PENDING) {
		then = time_uptime;
		do {
			code = AAC_GET_FWSTATUS(sc);
			if (time_uptime > (then + AAC_FWUPD_TIMEOUT)) {
				device_printf(sc->aac_dev,
						  "FATAL: controller not coming ready, "
						   "status %x\n", code);
				return(ENXIO);
			}
		} while (!(code & AAC_FLASH_UPD_SUCCESS) && !(code & AAC_FLASH_UPD_FAILED));
		/* 
		 * Delay 10 seconds. Because right now FW is doing a soft reset,
		 * do not read scratch pad register at this time
		 */
		waitCount = 10 * 10000;
		while (waitCount) {
			DELAY(100);		/* delay 100 microseconds */
			waitCount--;
		}
	}

	/*
	 * Wait for the adapter to come ready.
	 */
	then = time_uptime;
	do {
		code = AAC_GET_FWSTATUS(sc);
		if (time_uptime > (then + AAC_BOOT_TIMEOUT)) {
			device_printf(sc->aac_dev,
				      "FATAL: controller not coming ready, "
					   "status %x\n", code);
			return(ENXIO);
		}
	} while (!(code & AAC_UP_AND_RUNNING) || code == 0xffffffff);

	/*
	 * Retrieve the firmware version numbers.  Dell PERC2/QC cards with
	 * firmware version 1.x are not compatible with this driver.
	 */
	if (sc->flags & AAC_FLAGS_PERC2QC) {
		if (aacraid_sync_command(sc, AAC_MONKER_GETKERNVER, 0, 0, 0, 0,
				     NULL, NULL)) {
			device_printf(sc->aac_dev,
				      "Error reading firmware version\n");
			return (EIO);
		}

		/* These numbers are stored as ASCII! */
		major = (AAC_GET_MAILBOX(sc, 1) & 0xff) - 0x30;
		minor = (AAC_GET_MAILBOX(sc, 2) & 0xff) - 0x30;
		if (major == 1) {
			device_printf(sc->aac_dev,
			    "Firmware version %d.%d is not supported.\n",
			    major, minor);
			return (EINVAL);
		}
	}
	/*
	 * Retrieve the capabilities/supported options word so we know what
	 * work-arounds to enable.  Some firmware revs don't support this
	 * command.
	 */
	if (aacraid_sync_command(sc, AAC_MONKER_GETINFO, 0, 0, 0, 0, &status, NULL)) {
		if (status != AAC_SRB_STS_INVALID_REQUEST) {
			device_printf(sc->aac_dev,
			     "RequestAdapterInfo failed\n");
			return (EIO);
		}
	} else {
		options = AAC_GET_MAILBOX(sc, 1);
		atu_size = AAC_GET_MAILBOX(sc, 2);
		sc->supported_options = options;
		sc->doorbell_mask = AAC_GET_MAILBOX(sc, 3);

		if ((options & AAC_SUPPORTED_4GB_WINDOW) != 0 &&
		    (sc->flags & AAC_FLAGS_NO4GB) == 0)
			sc->flags |= AAC_FLAGS_4GB_WINDOW;
		if (options & AAC_SUPPORTED_NONDASD)
			sc->flags |= AAC_FLAGS_ENABLE_CAM;
		if ((options & AAC_SUPPORTED_SGMAP_HOST64) != 0
			&& (sizeof(bus_addr_t) > 4)
			&& (sc->hint_flags & 0x1)) {
			device_printf(sc->aac_dev,
			    "Enabling 64-bit address support\n");
			sc->flags |= AAC_FLAGS_SG_64BIT;
		}
		if (sc->aac_if.aif_send_command) {
			if (options & AAC_SUPPORTED_NEW_COMM_TYPE2)
				sc->flags |= AAC_FLAGS_NEW_COMM | AAC_FLAGS_NEW_COMM_TYPE2;
			else if (options & AAC_SUPPORTED_NEW_COMM_TYPE1)
				sc->flags |= AAC_FLAGS_NEW_COMM | AAC_FLAGS_NEW_COMM_TYPE1;
			else if ((options & AAC_SUPPORTED_NEW_COMM_TYPE3) ||
				(options & AAC_SUPPORTED_NEW_COMM_TYPE4))
				sc->flags |= AAC_FLAGS_NEW_COMM | AAC_FLAGS_NEW_COMM_TYPE34;
		}
		if (options & AAC_SUPPORTED_64BIT_ARRAYSIZE)
			sc->flags |= AAC_FLAGS_ARRAY_64BIT;
	}

	if (!(sc->flags & AAC_FLAGS_NEW_COMM)) {
		device_printf(sc->aac_dev, "Communication interface not supported!\n");
		return (ENXIO);
	}

	if (sc->hint_flags & 2) {
		device_printf(sc->aac_dev, 
			"Sync. mode enforced by driver parameter. This will cause a significant performance decrease!\n");
		sc->flags |= AAC_FLAGS_SYNC_MODE;
	} else if (sc->flags & AAC_FLAGS_NEW_COMM_TYPE34) {
		device_printf(sc->aac_dev, 
			"Async. mode not supported by current driver, sync. mode enforced.\nPlease update driver to get full performance.\n");
		sc->flags |= AAC_FLAGS_SYNC_MODE;
	}

	/* Check for broken hardware that does a lower number of commands */
	sc->aac_max_fibs = (sc->flags & AAC_FLAGS_256FIBS ? 256:512);

	/* Remap mem. resource, if required */
	if (atu_size > rman_get_size(sc->aac_regs_res0)) {
		bus_release_resource(
			sc->aac_dev, SYS_RES_MEMORY,
			sc->aac_regs_rid0, sc->aac_regs_res0);
		sc->aac_regs_res0 = bus_alloc_resource_anywhere(
			sc->aac_dev, SYS_RES_MEMORY, &sc->aac_regs_rid0,
			atu_size, RF_ACTIVE);
		if (sc->aac_regs_res0 == NULL) {
			sc->aac_regs_res0 = bus_alloc_resource_any(
				sc->aac_dev, SYS_RES_MEMORY,
				&sc->aac_regs_rid0, RF_ACTIVE);
			if (sc->aac_regs_res0 == NULL) {
				device_printf(sc->aac_dev,
					"couldn't allocate register window\n");
				return (ENXIO);
			}
		}
		sc->aac_btag0 = rman_get_bustag(sc->aac_regs_res0);
		sc->aac_bhandle0 = rman_get_bushandle(sc->aac_regs_res0);
	}

	/* Read preferred settings */
	sc->aac_max_fib_size = sizeof(struct aac_fib);
	sc->aac_max_sectors = 128;				/* 64KB */
	sc->aac_max_aif = 1;
	if (sc->flags & AAC_FLAGS_SG_64BIT)
		sc->aac_sg_tablesize = (AAC_FIB_DATASIZE
		 - sizeof(struct aac_blockwrite64))
		 / sizeof(struct aac_sg_entry64);
	else
		sc->aac_sg_tablesize = (AAC_FIB_DATASIZE
		 - sizeof(struct aac_blockwrite))
		 / sizeof(struct aac_sg_entry);

	if (!aacraid_sync_command(sc, AAC_MONKER_GETCOMMPREF, 0, 0, 0, 0, NULL, NULL)) {
		options = AAC_GET_MAILBOX(sc, 1);
		sc->aac_max_fib_size = (options & 0xFFFF);
		sc->aac_max_sectors = (options >> 16) << 1;
		options = AAC_GET_MAILBOX(sc, 2);
		sc->aac_sg_tablesize = (options >> 16);
		options = AAC_GET_MAILBOX(sc, 3);
		sc->aac_max_fibs = ((options >> 16) & 0xFFFF);
		if (sc->aac_max_fibs == 0 || sc->aac_hwif != AAC_HWIF_SRCV)
			sc->aac_max_fibs = (options & 0xFFFF);
		options = AAC_GET_MAILBOX(sc, 4);
		sc->aac_max_aif = (options & 0xFFFF);
		options = AAC_GET_MAILBOX(sc, 5);
		sc->aac_max_msix =(sc->flags & AAC_FLAGS_NEW_COMM_TYPE2) ? options : 0;
	}

	maxsize = sc->aac_max_fib_size + 31;
	if (sc->flags & AAC_FLAGS_NEW_COMM_TYPE1) 
		maxsize += sizeof(struct aac_fib_xporthdr);
	if (maxsize > PAGE_SIZE) {
    	sc->aac_max_fib_size -= (maxsize - PAGE_SIZE);
		maxsize = PAGE_SIZE;
	}
	sc->aac_max_fibs_alloc = PAGE_SIZE / maxsize;

	if (sc->aac_max_fib_size > sizeof(struct aac_fib)) {
		sc->flags |= AAC_FLAGS_RAW_IO;
		device_printf(sc->aac_dev, "Enable Raw I/O\n");
	}
	if ((sc->flags & AAC_FLAGS_RAW_IO) &&
	    (sc->flags & AAC_FLAGS_ARRAY_64BIT)) {
		sc->flags |= AAC_FLAGS_LBA_64BIT;
		device_printf(sc->aac_dev, "Enable 64-bit array\n");
	}

#ifdef AACRAID_DEBUG
	aacraid_get_fw_debug_buffer(sc);
#endif
	return (0);
}