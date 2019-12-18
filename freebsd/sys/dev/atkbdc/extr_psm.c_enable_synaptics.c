#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  synhw ;
struct TYPE_6__ {int infoMinor; int infoMajor; int infoRot180; int infoPortrait; int infoSensor; int infoHardware; int infoNewAbs; int capPen; int infoSimplC; int infoGeometry; int capExtended; int nExtendedQueries; int capMiddle; int capPassthrough; int capLowPower; int capMultiFingerReport; int capSleep; int capFourButtons; int capBallistics; int capMultiFinger; int capPalmDetect; int infoXupmm; int infoYupmm; int verticalScroll; int horizontalScroll; int verticalWheel; int nExtendedButtons; int capEWmode; int capClickPad; int capDeluxeLEDs; int noAbsoluteFilter; int capReportsV; int capUniformClickPad; int capReportsMin; int capInterTouch; int capReportsMax; int capClearPad; int capAdvancedGestures; int capCoveredPad; int maximumXCoord; int maximumYCoord; int minimumXCoord; int minimumYCoord; int forcePad; int topButtonPad; } ;
typedef  TYPE_2__ synapticshw_t ;
struct psmcpnp_softc {int type; } ;
struct TYPE_5__ {int buttons; int /*<<< orphan*/  model; } ;
struct psm_softc {TYPE_1__ hw; TYPE_2__ synhw; int /*<<< orphan*/  unit; int /*<<< orphan*/  kbdc; } ;
typedef  enum probearg { ____Placeholder_probearg } probearg ;
typedef  int /*<<< orphan*/ * device_t ;
typedef  int /*<<< orphan*/  KBDC ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  MOUSE_MODEL_SYNAPTICS ; 
 int PROBE ; 
 int /*<<< orphan*/  PSMCPNP_DRIVER_NAME ; 
#define  PSMCPNP_FORCEPAD 129 
#define  PSMCPNP_TOPBUTTONPAD 128 
 int /*<<< orphan*/  SYNAPTICS_READ_CAPABILITIES ; 
 int /*<<< orphan*/  SYNAPTICS_READ_CAPABILITIES_CONT ; 
 int /*<<< orphan*/  SYNAPTICS_READ_EXTENDED ; 
 int /*<<< orphan*/  SYNAPTICS_READ_IDENTITY ; 
 int /*<<< orphan*/  SYNAPTICS_READ_MAX_COORDS ; 
 int /*<<< orphan*/  SYNAPTICS_READ_MIN_COORDS ; 
 int /*<<< orphan*/  SYNAPTICS_READ_MODEL_ID ; 
 int /*<<< orphan*/  SYNAPTICS_READ_MODES ; 
 int /*<<< orphan*/  SYNAPTICS_READ_RESOLUTIONS ; 
 int /*<<< orphan*/  SYNAPTICS_VERSION_GE (TYPE_2__,int,int) ; 
 int TRUE ; 
 int /*<<< orphan*/  VLOG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (TYPE_2__*,int) ; 
 int /*<<< orphan*/  devclass_find (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * devclass_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct psmcpnp_softc* device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enable_trackpoint (struct psm_softc*,int) ; 
 int get_mouse_status (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mouse_ext_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  set_mouse_scaling (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  synaptics_preferred_mode (struct psm_softc*) ; 
 int /*<<< orphan*/  synaptics_set_mode (struct psm_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synaptics_support ; 
 int /*<<< orphan*/  synaptics_sysctl_create_tree (struct psm_softc*,char*,char*) ; 
 scalar_t__ trackpoint_support ; 
 int verbose ; 

__attribute__((used)) static int
enable_synaptics(struct psm_softc *sc, enum probearg arg)
{
	device_t psmcpnp;
	struct psmcpnp_softc *psmcpnp_sc;
	KBDC kbdc = sc->kbdc;
	synapticshw_t synhw;
	int status[3];
	int buttons;

	VLOG(3, (LOG_DEBUG, "synaptics: BEGIN init\n"));

	/*
	 * Just to be on the safe side: this avoids troubles with
	 * following mouse_ext_command() when the previous command
	 * was PSMC_SET_RESOLUTION. Set Scaling has no effect on
	 * Synaptics Touchpad behaviour.
	 */
	set_mouse_scaling(kbdc, 1);

	/* Identify the Touchpad version. */
	if (mouse_ext_command(kbdc, SYNAPTICS_READ_IDENTITY) == 0)
		return (FALSE);
	if (get_mouse_status(kbdc, status, 0, 3) != 3)
		return (FALSE);
	if (status[1] != 0x47)
		return (FALSE);

	bzero(&synhw, sizeof(synhw));
	synhw.infoMinor = status[0];
	synhw.infoMajor = status[2] & 0x0f;

	if (verbose >= 2)
		printf("Synaptics Touchpad v%d.%d\n", synhw.infoMajor,
		    synhw.infoMinor);

	if (synhw.infoMajor < 4) {
		printf("  Unsupported (pre-v4) Touchpad detected\n");
		return (FALSE);
	}

	/* Get the Touchpad model information. */
	if (mouse_ext_command(kbdc, SYNAPTICS_READ_MODEL_ID) == 0)
		return (FALSE);
	if (get_mouse_status(kbdc, status, 0, 3) != 3)
		return (FALSE);
	if ((status[1] & 0x01) != 0) {
		printf("  Failed to read model information\n");
		return (FALSE);
	}

	synhw.infoRot180   = (status[0] & 0x80) != 0;
	synhw.infoPortrait = (status[0] & 0x40) != 0;
	synhw.infoSensor   =  status[0] & 0x3f;
	synhw.infoHardware = (status[1] & 0xfe) >> 1;
	synhw.infoNewAbs   = (status[2] & 0x80) != 0;
	synhw.capPen       = (status[2] & 0x40) != 0;
	synhw.infoSimplC   = (status[2] & 0x20) != 0;
	synhw.infoGeometry =  status[2] & 0x0f;

	if (verbose >= 2) {
		printf("  Model information:\n");
		printf("   infoRot180: %d\n", synhw.infoRot180);
		printf("   infoPortrait: %d\n", synhw.infoPortrait);
		printf("   infoSensor: %d\n", synhw.infoSensor);
		printf("   infoHardware: %d\n", synhw.infoHardware);
		printf("   infoNewAbs: %d\n", synhw.infoNewAbs);
		printf("   capPen: %d\n", synhw.capPen);
		printf("   infoSimplC: %d\n", synhw.infoSimplC);
		printf("   infoGeometry: %d\n", synhw.infoGeometry);
	}

	/* Read the extended capability bits. */
	if (mouse_ext_command(kbdc, SYNAPTICS_READ_CAPABILITIES) == 0)
		return (FALSE);
	if (get_mouse_status(kbdc, status, 0, 3) != 3)
		return (FALSE);
	if (!SYNAPTICS_VERSION_GE(synhw, 7, 5) && status[1] != 0x47) {
		printf("  Failed to read extended capability bits\n");
		return (FALSE);
	}

	psmcpnp = devclass_get_device(devclass_find(PSMCPNP_DRIVER_NAME),
	    sc->unit);
	psmcpnp_sc = (psmcpnp != NULL) ? device_get_softc(psmcpnp) : NULL;

	/* Set the different capabilities when they exist. */
	buttons = 0;
	synhw.capExtended = (status[0] & 0x80) != 0;
	if (synhw.capExtended) {
		synhw.nExtendedQueries = (status[0] & 0x70) >> 4;
		synhw.capMiddle        = (status[0] & 0x04) != 0;
		synhw.capPassthrough   = (status[2] & 0x80) != 0;
		synhw.capLowPower      = (status[2] & 0x40) != 0;
		synhw.capMultiFingerReport =
					 (status[2] & 0x20) != 0;
		synhw.capSleep         = (status[2] & 0x10) != 0;
		synhw.capFourButtons   = (status[2] & 0x08) != 0;
		synhw.capBallistics    = (status[2] & 0x04) != 0;
		synhw.capMultiFinger   = (status[2] & 0x02) != 0;
		synhw.capPalmDetect    = (status[2] & 0x01) != 0;

		if (!set_mouse_scaling(kbdc, 1))
			return (FALSE);
		if (mouse_ext_command(kbdc, SYNAPTICS_READ_RESOLUTIONS) == 0)
			return (FALSE);
		if (get_mouse_status(kbdc, status, 0, 3) != 3)
			return (FALSE);

		if (status[0] != 0 && (status[1] & 0x80) && status[2] != 0) {
			synhw.infoXupmm = status[0];
			synhw.infoYupmm = status[2];
		}

		if (verbose >= 2) {
			printf("  Extended capabilities:\n");
			printf("   capExtended: %d\n", synhw.capExtended);
			printf("   capMiddle: %d\n", synhw.capMiddle);
			printf("   nExtendedQueries: %d\n",
			    synhw.nExtendedQueries);
			printf("   capPassthrough: %d\n", synhw.capPassthrough);
			printf("   capLowPower: %d\n", synhw.capLowPower);
			printf("   capMultiFingerReport: %d\n",
			    synhw.capMultiFingerReport);
			printf("   capSleep: %d\n", synhw.capSleep);
			printf("   capFourButtons: %d\n", synhw.capFourButtons);
			printf("   capBallistics: %d\n", synhw.capBallistics);
			printf("   capMultiFinger: %d\n", synhw.capMultiFinger);
			printf("   capPalmDetect: %d\n", synhw.capPalmDetect);
			printf("   infoXupmm: %d\n", synhw.infoXupmm);
			printf("   infoYupmm: %d\n", synhw.infoYupmm);
		}

		/*
		 * If nExtendedQueries is 1 or greater, then the TouchPad
		 * supports this number of extended queries. We can load
		 * more information about buttons using query 0x09.
		 */
		if (synhw.nExtendedQueries >= 1) {
			if (!set_mouse_scaling(kbdc, 1))
				return (FALSE);
			if (mouse_ext_command(kbdc,
			    SYNAPTICS_READ_EXTENDED) == 0)
				return (FALSE);
			if (get_mouse_status(kbdc, status, 0, 3) != 3)
				return (FALSE);
			synhw.verticalScroll   = (status[0] & 0x01) != 0;
			synhw.horizontalScroll = (status[0] & 0x02) != 0;
			synhw.verticalWheel    = (status[0] & 0x08) != 0;
			synhw.nExtendedButtons = (status[1] & 0xf0) >> 4;
			synhw.capEWmode        = (status[0] & 0x04) != 0;
			if (verbose >= 2) {
				printf("  Extended model ID:\n");
				printf("   verticalScroll: %d\n",
				    synhw.verticalScroll);
				printf("   horizontalScroll: %d\n",
				    synhw.horizontalScroll);
				printf("   verticalWheel: %d\n",
				    synhw.verticalWheel);
				printf("   nExtendedButtons: %d\n",
				    synhw.nExtendedButtons);
				printf("   capEWmode: %d\n",
				    synhw.capEWmode);
			}
			/*
			 * Add the number of extended buttons to the total
			 * button support count, including the middle button
			 * if capMiddle support bit is set.
			 */
			buttons = synhw.nExtendedButtons + synhw.capMiddle;
		} else
			/*
			 * If the capFourButtons support bit is set,
			 * add a fourth button to the total button count.
			 */
			buttons = synhw.capFourButtons ? 1 : 0;

		/* Read the continued capabilities bits. */
		if (synhw.nExtendedQueries >= 4) {
			if (!set_mouse_scaling(kbdc, 1))
				return (FALSE);
			if (mouse_ext_command(kbdc,
			    SYNAPTICS_READ_CAPABILITIES_CONT) == 0)
				return (FALSE);
			if (get_mouse_status(kbdc, status, 0, 3) != 3)
				return (FALSE);

			synhw.capClickPad         = (status[1] & 0x01) << 1;
			synhw.capClickPad        |= (status[0] & 0x10) != 0;
			synhw.capDeluxeLEDs       = (status[1] & 0x02) != 0;
			synhw.noAbsoluteFilter    = (status[1] & 0x04) != 0;
			synhw.capReportsV         = (status[1] & 0x08) != 0;
			synhw.capUniformClickPad  = (status[1] & 0x10) != 0;
			synhw.capReportsMin       = (status[1] & 0x20) != 0;
			synhw.capInterTouch       = (status[1] & 0x40) != 0;
			synhw.capReportsMax       = (status[0] & 0x02) != 0;
			synhw.capClearPad         = (status[0] & 0x04) != 0;
			synhw.capAdvancedGestures = (status[0] & 0x08) != 0;
			synhw.capCoveredPad       = (status[0] & 0x80) != 0;

			if (synhw.capReportsMax) {
				if (!set_mouse_scaling(kbdc, 1))
					return (FALSE);
				if (mouse_ext_command(kbdc,
				    SYNAPTICS_READ_MAX_COORDS) == 0)
					return (FALSE);
				if (get_mouse_status(kbdc, status, 0, 3) != 3)
					return (FALSE);

				synhw.maximumXCoord = (status[0] << 5) |
						     ((status[1] & 0x0f) << 1);
				synhw.maximumYCoord = (status[2] << 5) |
						     ((status[1] & 0xf0) >> 3);
			} else {
				/*
				 * Typical bezel limits. Taken from 'Synaptics
				 * PS/2 * TouchPad Interfacing Guide' p.3.2.3.
				 */
				synhw.maximumXCoord = 5472;
				synhw.maximumYCoord = 4448;
			}

			if (synhw.capReportsMin) {
				if (!set_mouse_scaling(kbdc, 1))
					return (FALSE);
				if (mouse_ext_command(kbdc,
				    SYNAPTICS_READ_MIN_COORDS) == 0)
					return (FALSE);
				if (get_mouse_status(kbdc, status, 0, 3) != 3)
					return (FALSE);

				synhw.minimumXCoord = (status[0] << 5) |
						     ((status[1] & 0x0f) << 1);
				synhw.minimumYCoord = (status[2] << 5) |
						     ((status[1] & 0xf0) >> 3);
			} else {
				/*
				 * Typical bezel limits. Taken from 'Synaptics
				 * PS/2 * TouchPad Interfacing Guide' p.3.2.3.
				 */
				synhw.minimumXCoord = 1472;
				synhw.minimumYCoord = 1408;
			}

			/*
			 * ClickPad properties are not exported through PS/2
			 * protocol. Detection is based on controller's PnP ID.
			 */
			if (synhw.capClickPad && psmcpnp_sc != NULL) {
				switch (psmcpnp_sc->type) {
				case PSMCPNP_FORCEPAD:
					synhw.forcePad = 1;
					break;
				case PSMCPNP_TOPBUTTONPAD:
					synhw.topButtonPad = 1;
					break;
				default:
					break;
				}
			}

			if (verbose >= 2) {
				printf("  Continued capabilities:\n");
				printf("   capClickPad: %d\n",
				       synhw.capClickPad);
				printf("   capDeluxeLEDs: %d\n",
				       synhw.capDeluxeLEDs);
				printf("   noAbsoluteFilter: %d\n",
				       synhw.noAbsoluteFilter);
				printf("   capReportsV: %d\n",
				       synhw.capReportsV);
				printf("   capUniformClickPad: %d\n",
				       synhw.capUniformClickPad);
				printf("   capReportsMin: %d\n",
				       synhw.capReportsMin);
				printf("   capInterTouch: %d\n",
				       synhw.capInterTouch);
				printf("   capReportsMax: %d\n",
				       synhw.capReportsMax);
				printf("   capClearPad: %d\n",
				       synhw.capClearPad);
				printf("   capAdvancedGestures: %d\n",
				       synhw.capAdvancedGestures);
				printf("   capCoveredPad: %d\n",
				       synhw.capCoveredPad);
				if (synhw.capReportsMax) {
					printf("   maximumXCoord: %d\n",
					       synhw.maximumXCoord);
					printf("   maximumYCoord: %d\n",
					       synhw.maximumYCoord);
				}
				if (synhw.capReportsMin) {
					printf("   minimumXCoord: %d\n",
					       synhw.minimumXCoord);
					printf("   minimumYCoord: %d\n",
					       synhw.minimumYCoord);
				}
				if (synhw.capClickPad) {
					printf("  Clickpad capabilities:\n");
					printf("   forcePad: %d\n",
					       synhw.forcePad);
					printf("   topButtonPad: %d\n",
					       synhw.topButtonPad);
				}
			}
			buttons += synhw.capClickPad;
		}
	}

	if (verbose >= 2) {
		if (synhw.capExtended)
			printf("  Additional Buttons: %d\n", buttons);
		else
			printf("  No extended capabilities\n");
	}

	/*
	 * Add the default number of 3 buttons to the total
	 * count of supported buttons reported above.
	 */
	buttons += 3;

	/*
	 * Read the mode byte.
	 *
	 * XXX: Note the Synaptics documentation also defines the first
	 * byte of the response to this query to be a constant 0x3b, this
	 * does not appear to be true for Touchpads with guest devices.
	 */
	if (mouse_ext_command(kbdc, SYNAPTICS_READ_MODES) == 0)
		return (FALSE);
	if (get_mouse_status(kbdc, status, 0, 3) != 3)
		return (FALSE);
	if (!SYNAPTICS_VERSION_GE(synhw, 7, 5) && status[1] != 0x47) {
		printf("  Failed to read mode byte\n");
		return (FALSE);
	}

	if (arg == PROBE)
		sc->synhw = synhw;
	if (!synaptics_support)
		return (FALSE);

	/* Set mouse type just now for synaptics_set_mode() */
	sc->hw.model = MOUSE_MODEL_SYNAPTICS;

	synaptics_set_mode(sc, synaptics_preferred_mode(sc));

	if (trackpoint_support && synhw.capPassthrough) {
		enable_trackpoint(sc, arg);
	}

	VLOG(3, (LOG_DEBUG, "synaptics: END init (%d buttons)\n", buttons));

	if (arg == PROBE) {
		/* Create sysctl tree. */
		synaptics_sysctl_create_tree(sc, "synaptics",
		    "Synaptics TouchPad");
		sc->hw.buttons = buttons;
	}

	return (TRUE);
}