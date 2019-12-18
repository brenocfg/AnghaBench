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
struct TYPE_3__ {int /*<<< orphan*/  wLength; int /*<<< orphan*/  wIndex; int /*<<< orphan*/  wValue; int /*<<< orphan*/  bRequest; int /*<<< orphan*/  bmRequestType; } ;
typedef  TYPE_1__ usb_device_request_t ;
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
typedef  scalar_t__ u_char ;
struct run_softc {int mac_ver; int sc_flags; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_udev; } ;
struct firmware {int datasize; scalar_t__* data; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  FIRMWARE_UNLOAD ; 
 int /*<<< orphan*/  RT2860_H2M_BBPAGENT ; 
 int /*<<< orphan*/  RT2860_H2M_INTSRC ; 
 int /*<<< orphan*/  RT2860_H2M_MAILBOX ; 
 int /*<<< orphan*/  RT2860_H2M_MAILBOX_CID ; 
 int /*<<< orphan*/  RT2860_H2M_MAILBOX_STATUS ; 
 int /*<<< orphan*/  RT2860_MCU_CMD_RFRESET ; 
 int RT2860_MCU_READY ; 
 int /*<<< orphan*/  RT2860_SYS_CTRL ; 
 int /*<<< orphan*/  RT2870_FW_BASE ; 
 int /*<<< orphan*/  RT2870_RESET ; 
 int RUN_FLAG_FWLOAD_NEEDED ; 
 int /*<<< orphan*/  RUN_LOCK (struct run_softc*) ; 
 int /*<<< orphan*/  RUN_UNLOCK (struct run_softc*) ; 
 int /*<<< orphan*/  USETW (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UT_WRITE_VENDOR_DEVICE ; 
 scalar_t__ be64toh (int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 struct firmware* firmware_get (char*) ; 
 int /*<<< orphan*/  firmware_put (struct firmware const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  run_delay (struct run_softc*,int) ; 
 int run_mcu_cmd (struct run_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int run_read (struct run_softc*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  run_write (struct run_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  run_write_region_1 (struct run_softc*,int /*<<< orphan*/ ,scalar_t__ const*,int) ; 
 int usbd_do_request (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
run_load_microcode(struct run_softc *sc)
{
	usb_device_request_t req;
	const struct firmware *fw;
	const u_char *base;
	uint32_t tmp;
	int ntries, error;
	const uint64_t *temp;
	uint64_t bytes;

	RUN_UNLOCK(sc);
	fw = firmware_get("runfw");
	RUN_LOCK(sc);
	if (fw == NULL) {
		device_printf(sc->sc_dev,
		    "failed loadfirmware of file %s\n", "runfw");
		return ENOENT;
	}

	if (fw->datasize != 8192) {
		device_printf(sc->sc_dev,
		    "invalid firmware size (should be 8KB)\n");
		error = EINVAL;
		goto fail;
	}

	/*
	 * RT3071/RT3072 use a different firmware
	 * run-rt2870 (8KB) contains both,
	 * first half (4KB) is for rt2870,
	 * last half is for rt3071.
	 */
	base = fw->data;
	if ((sc->mac_ver) != 0x2860 &&
	    (sc->mac_ver) != 0x2872 &&
	    (sc->mac_ver) != 0x3070) { 
		base += 4096;
	}

	/* cheap sanity check */
	temp = fw->data;
	bytes = *temp;
	if (bytes != be64toh(0xffffff0210280210ULL)) {
		device_printf(sc->sc_dev, "firmware checksum failed\n");
		error = EINVAL;
		goto fail;
	}

	/* write microcode image */
	if (sc->sc_flags & RUN_FLAG_FWLOAD_NEEDED) {
		run_write_region_1(sc, RT2870_FW_BASE, base, 4096);
		run_write(sc, RT2860_H2M_MAILBOX_CID, 0xffffffff);
		run_write(sc, RT2860_H2M_MAILBOX_STATUS, 0xffffffff);
	}

	req.bmRequestType = UT_WRITE_VENDOR_DEVICE;
	req.bRequest = RT2870_RESET;
	USETW(req.wValue, 8);
	USETW(req.wIndex, 0);
	USETW(req.wLength, 0);
	if ((error = usbd_do_request(sc->sc_udev, &sc->sc_mtx, &req, NULL))
	    != 0) {
		device_printf(sc->sc_dev, "firmware reset failed\n");
		goto fail;
	}

	run_delay(sc, 10);

	run_write(sc, RT2860_H2M_BBPAGENT, 0);
	run_write(sc, RT2860_H2M_MAILBOX, 0);
	run_write(sc, RT2860_H2M_INTSRC, 0);
	if ((error = run_mcu_cmd(sc, RT2860_MCU_CMD_RFRESET, 0)) != 0)
		goto fail;

	/* wait until microcontroller is ready */
	for (ntries = 0; ntries < 1000; ntries++) {
		if ((error = run_read(sc, RT2860_SYS_CTRL, &tmp)) != 0)
			goto fail;
		if (tmp & RT2860_MCU_READY)
			break;
		run_delay(sc, 10);
	}
	if (ntries == 1000) {
		device_printf(sc->sc_dev,
		    "timeout waiting for MCU to initialize\n");
		error = ETIMEDOUT;
		goto fail;
	}
	device_printf(sc->sc_dev, "firmware %s ver. %u.%u loaded\n",
	    (base == fw->data) ? "RT2870" : "RT3071",
	    *(base + 4092), *(base + 4093));

fail:
	firmware_put(fw, FIRMWARE_UNLOAD);
	return (error);
}