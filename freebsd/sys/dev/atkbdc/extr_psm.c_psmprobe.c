#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int rate; int resolution; int accelfactor; int /*<<< orphan*/  packetsize; int /*<<< orphan*/ * syncmask; int /*<<< orphan*/  level; } ;
struct TYPE_4__ {int hwid; int buttons; int /*<<< orphan*/  model; int /*<<< orphan*/  type; int /*<<< orphan*/  iftype; } ;
struct psm_softc {int unit; int config; int /*<<< orphan*/  kbdc; TYPE_2__ mode; TYPE_2__ dflt_mode; int /*<<< orphan*/  flags; TYPE_1__ hw; int /*<<< orphan*/  muxport; int /*<<< orphan*/ * intr; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_6__ {int /*<<< orphan*/  packetsize; int /*<<< orphan*/  syncmask; int /*<<< orphan*/  model; scalar_t__ (* probefunc ) (struct psm_softc*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ ALWAYS_RESTORE_CONTROLLER (int /*<<< orphan*/ ) ; 
 int ENXIO ; 
 int /*<<< orphan*/  FALSE ; 
 int GENERIC_MOUSE_ENTRY ; 
 int /*<<< orphan*/  KBDC_ENABLE_AUX_PORT ; 
 int KBDC_RID_AUX ; 
 int KBD_AUX_CONTROL_BITS ; 
 int KBD_DISABLE_AUX_INT ; 
 int KBD_DISABLE_AUX_PORT ; 
 int KBD_DISABLE_KBD_INT ; 
 int KBD_DISABLE_KBD_PORT ; 
 int KBD_ENABLE_AUX_PORT ; 
 int KBD_KBD_CONTROL_BITS ; 
 int /*<<< orphan*/  MOUSE_IF_PS2 ; 
 int /*<<< orphan*/  MOUSE_MOUSE ; 
 int /*<<< orphan*/  MOUSE_PS2_PACKETSIZE ; 
 int /*<<< orphan*/  MOUSE_PS2_TAP ; 
 int /*<<< orphan*/  MOUSE_TRACKBALL ; 
 int /*<<< orphan*/  MOUSE_UNKNOWN ; 
 int /*<<< orphan*/  PROBE ; 
 int /*<<< orphan*/  PSMC_SET_DEFAULTS ; 
#define  PSM_4DMOUSE_ID 134 
#define  PSM_4DPLUS_ID 133 
#define  PSM_ACK 132 
#define  PSM_BALLPOINT_ID 131 
 int PSM_CONFIG_ACCEL ; 
 int PSM_CONFIG_FLAGS ; 
 int PSM_CONFIG_FORCETAP ; 
 int /*<<< orphan*/  PSM_CONFIG_HOOKRESUME ; 
 int PSM_CONFIG_IGNPORTERROR ; 
 int PSM_CONFIG_INITAFTERSUSPEND ; 
 int PSM_CONFIG_NOCHECKSYNC ; 
 int PSM_CONFIG_NOIDPROBE ; 
 int PSM_CONFIG_NORESET ; 
 int PSM_CONFIG_RESOLUTION ; 
#define  PSM_EXPLORER_ID 130 
#define  PSM_INTELLI_ID 129 
 int /*<<< orphan*/  PSM_LEVEL_BASE ; 
#define  PSM_MOUSE_ID 128 
 int /*<<< orphan*/  PSM_NEED_SYNCBITS ; 
 int /*<<< orphan*/  PSM_NOMUX ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  atkbdc_open (int) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int device_get_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct psm_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  disable_aux_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  empty_both_buffers (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  enable_aux_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  endprobe (int) ; 
 int get_aux_id (int /*<<< orphan*/ ) ; 
 int get_controller_command_byte (int /*<<< orphan*/ ) ; 
 int get_mouse_buttons (int /*<<< orphan*/ ) ; 
 int get_mouse_status (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  is_a_mouse (int) ; 
 int /*<<< orphan*/  kbdc_debug (int /*<<< orphan*/ ) ; 
 int kbdc_get_device_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kbdc_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kbdc_set_device_mask (int /*<<< orphan*/ ,int) ; 
 char* model_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 int /*<<< orphan*/  recover_from_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_aux_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  restore_controller (int /*<<< orphan*/ ,int) ; 
 int send_aux_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_controller_command_byte (int /*<<< orphan*/ ,int,int) ; 
 void* set_mouse_resolution (int /*<<< orphan*/ ,int) ; 
 int set_mouse_sampling_rate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_mouse_scaling (int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (struct psm_softc*,int /*<<< orphan*/ ) ; 
 int test_aux_port (int /*<<< orphan*/ ) ; 
 TYPE_3__* vendortype ; 
 int verbose ; 
 int /*<<< orphan*/  write_controller_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
psmprobe(device_t dev)
{
	int unit = device_get_unit(dev);
	struct psm_softc *sc = device_get_softc(dev);
	int stat[3];
	int command_byte;
	int mask;
	int rid;
	int i;

#if 0
	kbdc_debug(TRUE);
#endif

	/* see if IRQ is available */
	rid = KBDC_RID_AUX;
	sc->intr = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid, RF_ACTIVE);
	if (sc->intr == NULL) {
		if (bootverbose)
			device_printf(dev, "unable to allocate IRQ\n");
		return (ENXIO);
	}
	bus_release_resource(dev, SYS_RES_IRQ, rid, sc->intr);

	sc->unit = unit;
	sc->kbdc = atkbdc_open(device_get_unit(device_get_parent(dev)));
	sc->config = device_get_flags(dev) & PSM_CONFIG_FLAGS;
	/* XXX: for backward compatibility */
#if defined(PSM_HOOKRESUME) || defined(PSM_HOOKAPM)
	sc->config |=
#ifdef PSM_RESETAFTERSUSPEND
	PSM_CONFIG_INITAFTERSUSPEND;
#else
	PSM_CONFIG_HOOKRESUME;
#endif
#endif /* PSM_HOOKRESUME | PSM_HOOKAPM */
	sc->flags = 0;
	sc->muxport = PSM_NOMUX;
	if (bootverbose)
		++verbose;

	device_set_desc(dev, "PS/2 Mouse");

	if (!kbdc_lock(sc->kbdc, TRUE)) {
		printf("psm%d: unable to lock the controller.\n", unit);
		if (bootverbose)
			--verbose;
		return (ENXIO);
	}

	/*
	 * NOTE: two bits in the command byte controls the operation of the
	 * aux port (mouse port): the aux port disable bit (bit 5) and the aux
	 * port interrupt (IRQ 12) enable bit (bit 2).
	 */

	/* discard anything left after the keyboard initialization */
	empty_both_buffers(sc->kbdc, 10);

	/* save the current command byte; it will be used later */
	mask = kbdc_get_device_mask(sc->kbdc) & ~KBD_AUX_CONTROL_BITS;
	command_byte = get_controller_command_byte(sc->kbdc);
	if (verbose)
		printf("psm%d: current command byte:%04x\n", unit,
		    command_byte);
	if (command_byte == -1) {
		/* CONTROLLER ERROR */
		printf("psm%d: unable to get the current command byte value.\n",
			unit);
		endprobe(ENXIO);
	}

	/*
	 * disable the keyboard port while probing the aux port, which must be
	 * enabled during this routine
	 */
	if (!set_controller_command_byte(sc->kbdc,
	    KBD_KBD_CONTROL_BITS | KBD_AUX_CONTROL_BITS,
	    KBD_DISABLE_KBD_PORT | KBD_DISABLE_KBD_INT |
	    KBD_ENABLE_AUX_PORT | KBD_DISABLE_AUX_INT)) {
		/*
		 * this is CONTROLLER ERROR; I don't know how to recover
		 * from this error...
		 */
		if (ALWAYS_RESTORE_CONTROLLER(sc->kbdc))
			restore_controller(sc->kbdc, command_byte);
		printf("psm%d: unable to set the command byte.\n", unit);
		endprobe(ENXIO);
	}
	write_controller_command(sc->kbdc, KBDC_ENABLE_AUX_PORT);

	/*
	 * NOTE: `test_aux_port()' is designed to return with zero if the aux
	 * port exists and is functioning. However, some controllers appears
	 * to respond with zero even when the aux port doesn't exist. (It may
	 * be that this is only the case when the controller DOES have the aux
	 * port but the port is not wired on the motherboard.) The keyboard
	 * controllers without the port, such as the original AT, are
	 * supposed to return with an error code or simply time out. In any
	 * case, we have to continue probing the port even when the controller
	 * passes this test.
	 *
	 * XXX: some controllers erroneously return the error code 1, 2 or 3
	 * when it has a perfectly functional aux port. We have to ignore
	 * this error code. Even if the controller HAS error with the aux
	 * port, it will be detected later...
	 * XXX: another incompatible controller returns PSM_ACK (0xfa)...
	 */
	switch ((i = test_aux_port(sc->kbdc))) {
	case 1:		/* ignore these errors */
	case 2:
	case 3:
	case PSM_ACK:
		if (verbose)
			printf("psm%d: strange result for test aux port "
			    "(%d).\n", unit, i);
		/* FALLTHROUGH */
	case 0:		/* no error */
		break;
	case -1:	/* time out */
	default:	/* error */
		recover_from_error(sc->kbdc);
		if (sc->config & PSM_CONFIG_IGNPORTERROR)
			break;
		if (ALWAYS_RESTORE_CONTROLLER(sc->kbdc))
			restore_controller(sc->kbdc, command_byte);
		if (verbose)
			printf("psm%d: the aux port is not functioning (%d).\n",
			    unit, i);
		endprobe(ENXIO);
	}

	if (sc->config & PSM_CONFIG_NORESET) {
		/*
		 * Don't try to reset the pointing device.  It may possibly be
		 * left in an unknown state, though...
		 */
	} else {
		/*
		 * NOTE: some controllers appears to hang the `keyboard' when
		 * the aux port doesn't exist and `PSMC_RESET_DEV' is issued.
		 *
		 * Attempt to reset the controller twice -- this helps
		 * pierce through some KVM switches. The second reset
		 * is non-fatal.
		 */
		if (!reset_aux_dev(sc->kbdc)) {
			recover_from_error(sc->kbdc);
			if (ALWAYS_RESTORE_CONTROLLER(sc->kbdc))
				restore_controller(sc->kbdc, command_byte);
			if (verbose)
				printf("psm%d: failed to reset the aux "
				    "device.\n", unit);
			endprobe(ENXIO);
		} else if (!reset_aux_dev(sc->kbdc)) {
			recover_from_error(sc->kbdc);
			if (verbose >= 2)
				printf("psm%d: failed to reset the aux device "
				    "(2).\n", unit);
		}
	}

	/*
	 * both the aux port and the aux device are functioning, see if the
	 * device can be enabled. NOTE: when enabled, the device will start
	 * sending data; we shall immediately disable the device once we know
	 * the device can be enabled.
	 */
	if (!enable_aux_dev(sc->kbdc) || !disable_aux_dev(sc->kbdc)) {
		/* MOUSE ERROR */
		recover_from_error(sc->kbdc);
		if (ALWAYS_RESTORE_CONTROLLER(sc->kbdc))
			restore_controller(sc->kbdc, command_byte);
		if (verbose)
			printf("psm%d: failed to enable the aux device.\n",
			    unit);
		endprobe(ENXIO);
	}

	/* save the default values after reset */
	if (get_mouse_status(sc->kbdc, stat, 0, 3) >= 3) {
		sc->dflt_mode.rate = sc->mode.rate = stat[2];
		sc->dflt_mode.resolution = sc->mode.resolution = stat[1];
	} else {
		sc->dflt_mode.rate = sc->mode.rate = -1;
		sc->dflt_mode.resolution = sc->mode.resolution = -1;
	}

	/* hardware information */
	sc->hw.iftype = MOUSE_IF_PS2;

	/* verify the device is a mouse */
	sc->hw.hwid = get_aux_id(sc->kbdc);
	if (!is_a_mouse(sc->hw.hwid)) {
		if (ALWAYS_RESTORE_CONTROLLER(sc->kbdc))
			restore_controller(sc->kbdc, command_byte);
		if (verbose)
			printf("psm%d: unknown device type (%d).\n", unit,
			    sc->hw.hwid);
		endprobe(ENXIO);
	}
	switch (sc->hw.hwid) {
	case PSM_BALLPOINT_ID:
		sc->hw.type = MOUSE_TRACKBALL;
		break;
	case PSM_MOUSE_ID:
	case PSM_INTELLI_ID:
	case PSM_EXPLORER_ID:
	case PSM_4DMOUSE_ID:
	case PSM_4DPLUS_ID:
		sc->hw.type = MOUSE_MOUSE;
		break;
	default:
		sc->hw.type = MOUSE_UNKNOWN;
		break;
	}

	if (sc->config & PSM_CONFIG_NOIDPROBE) {
		sc->hw.buttons = 2;
		i = GENERIC_MOUSE_ENTRY;
	} else {
		/* # of buttons */
		sc->hw.buttons = get_mouse_buttons(sc->kbdc);

		/* other parameters */
		for (i = 0; vendortype[i].probefunc != NULL; ++i)
			if ((*vendortype[i].probefunc)(sc, PROBE)) {
				if (verbose >= 2)
					printf("psm%d: found %s\n", unit,
					    model_name(vendortype[i].model));
				break;
			}
	}

	sc->hw.model = vendortype[i].model;

	sc->dflt_mode.level = PSM_LEVEL_BASE;
	sc->dflt_mode.packetsize = MOUSE_PS2_PACKETSIZE;
	sc->dflt_mode.accelfactor = (sc->config & PSM_CONFIG_ACCEL) >> 4;
	if (sc->config & PSM_CONFIG_NOCHECKSYNC)
		sc->dflt_mode.syncmask[0] = 0;
	else
		sc->dflt_mode.syncmask[0] = vendortype[i].syncmask;
	if (sc->config & PSM_CONFIG_FORCETAP)
		sc->dflt_mode.syncmask[0] &= ~MOUSE_PS2_TAP;
	sc->dflt_mode.syncmask[1] = 0;	/* syncbits */
	sc->mode = sc->dflt_mode;
	sc->mode.packetsize = vendortype[i].packetsize;

	/* set mouse parameters */
#if 0
	/*
	 * A version of Logitech FirstMouse+ won't report wheel movement,
	 * if SET_DEFAULTS is sent...  Don't use this command.
	 * This fix was found by Takashi Nishida.
	 */
	i = send_aux_command(sc->kbdc, PSMC_SET_DEFAULTS);
	if (verbose >= 2)
		printf("psm%d: SET_DEFAULTS return code:%04x\n", unit, i);
#endif
	if (sc->config & PSM_CONFIG_RESOLUTION)
		sc->mode.resolution =
		    set_mouse_resolution(sc->kbdc,
		    (sc->config & PSM_CONFIG_RESOLUTION) - 1);
	else if (sc->mode.resolution >= 0)
		sc->mode.resolution =
		    set_mouse_resolution(sc->kbdc, sc->dflt_mode.resolution);
	if (sc->mode.rate > 0)
		sc->mode.rate =
		    set_mouse_sampling_rate(sc->kbdc, sc->dflt_mode.rate);
	set_mouse_scaling(sc->kbdc, 1);

	/* Record sync on the next data packet we see. */
	sc->flags |= PSM_NEED_SYNCBITS;

	/* just check the status of the mouse */
	/*
	 * NOTE: XXX there are some arcane controller/mouse combinations out
	 * there, which hung the controller unless there is data transmission
	 * after ACK from the mouse.
	 */
	if (get_mouse_status(sc->kbdc, stat, 0, 3) < 3)
		printf("psm%d: failed to get status.\n", unit);
	else {
		/*
		 * When in its native mode, some mice operate with different
		 * default parameters than in the PS/2 compatible mode.
		 */
		sc->dflt_mode.rate = sc->mode.rate = stat[2];
		sc->dflt_mode.resolution = sc->mode.resolution = stat[1];
	}

	/* disable the aux port for now... */
	if (!set_controller_command_byte(sc->kbdc,
	    KBD_KBD_CONTROL_BITS | KBD_AUX_CONTROL_BITS,
	    (command_byte & KBD_KBD_CONTROL_BITS) |
	    KBD_DISABLE_AUX_PORT | KBD_DISABLE_AUX_INT)) {
		/*
		 * this is CONTROLLER ERROR; I don't know the proper way to
		 * recover from this error...
		 */
		if (ALWAYS_RESTORE_CONTROLLER(sc->kbdc))
			restore_controller(sc->kbdc, command_byte);
		printf("psm%d: unable to set the command byte.\n", unit);
		endprobe(ENXIO);
	}

	/* done */
	kbdc_set_device_mask(sc->kbdc, mask | KBD_AUX_CONTROL_BITS);
	kbdc_lock(sc->kbdc, FALSE);
	return (0);
}