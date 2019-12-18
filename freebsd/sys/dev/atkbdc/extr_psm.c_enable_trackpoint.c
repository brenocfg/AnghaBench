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
struct TYPE_4__ {scalar_t__ capPassthrough; } ;
struct TYPE_3__ {int hwid; int buttons; } ;
struct psm_softc {int tphw; TYPE_2__ synhw; TYPE_1__ hw; int /*<<< orphan*/  kbdc; } ;
typedef  enum probearg { ____Placeholder_probearg } probearg ;
typedef  int /*<<< orphan*/  KBDC ;

/* Variables and functions */
 int FALSE ; 
 int PROBE ; 
 scalar_t__ PSM_ACK ; 
 int TRUE ; 
 int read_aux_data (int /*<<< orphan*/ ) ; 
 scalar_t__ send_aux_command (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_trackpoint_parameters (struct psm_softc*) ; 
 int /*<<< orphan*/  synaptics_passthrough_off (struct psm_softc*) ; 
 int /*<<< orphan*/  synaptics_passthrough_on (struct psm_softc*) ; 
 int /*<<< orphan*/  trackpoint_support ; 
 int /*<<< orphan*/  trackpoint_sysctl_create_tree (struct psm_softc*) ; 

__attribute__((used)) static int
enable_trackpoint(struct psm_softc *sc, enum probearg arg)
{
	KBDC kbdc = sc->kbdc;
	int id;

	/*
	 * If called from enable_synaptics(), make sure that passthrough
	 * mode is enabled so we can reach the trackpoint.
	 * However, passthrough mode must be disabled before setting the
	 * trackpoint parameters, as rackpoint_command() enables and disables
	 * passthrough mode on its own.
	 */
	if (sc->synhw.capPassthrough)
		synaptics_passthrough_on(sc);

	if (send_aux_command(kbdc, 0xe1) != PSM_ACK ||
	    read_aux_data(kbdc) != 0x01)
		goto no_trackpoint;
	id = read_aux_data(kbdc);
	if (id < 0x01)
		goto no_trackpoint;
	if (arg == PROBE)
		sc->tphw = id;
	if (!trackpoint_support)
		goto no_trackpoint;

	if (sc->synhw.capPassthrough)
		synaptics_passthrough_off(sc);

	if (arg == PROBE) {
		trackpoint_sysctl_create_tree(sc);
		/*
		 * Don't overwrite hwid and buttons when we are
		 * a guest device.
		 */
		if (!sc->synhw.capPassthrough) {
			sc->hw.hwid = id;
			sc->hw.buttons = 3;
		}
	}

	set_trackpoint_parameters(sc);

	return (TRUE);

no_trackpoint:
	if (sc->synhw.capPassthrough)
		synaptics_passthrough_off(sc);

	return (FALSE);
}