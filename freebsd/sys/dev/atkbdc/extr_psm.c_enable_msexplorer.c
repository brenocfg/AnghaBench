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
typedef  int u_char ;
struct TYPE_2__ {int buttons; int hwid; } ;
struct psm_softc {TYPE_1__ hw; int /*<<< orphan*/  kbdc; } ;
typedef  enum probearg { ____Placeholder_probearg } probearg ;
typedef  int /*<<< orphan*/  KBDC ;

/* Variables and functions */
 int FALSE ; 
 int PROBE ; 
 int PSM_EXPLORER_ID ; 
 int TRUE ; 
 int /*<<< orphan*/  enable_msintelli (struct psm_softc*,int) ; 
 int get_aux_id (int /*<<< orphan*/ ) ; 
 int nitems (int*) ; 
 int set_mouse_sampling_rate (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
enable_msexplorer(struct psm_softc *sc, enum probearg arg)
{
	KBDC kbdc = sc->kbdc;
	static u_char rate0[] = { 200, 100, 80, };
	static u_char rate1[] = { 200, 200, 80, };
	int id;
	int i;

	/*
	 * This is needed for at least A4Tech X-7xx mice - they do not go
	 * straight to Explorer mode, but need to be set to Intelli mode
	 * first.
	 */
	enable_msintelli(sc, arg);

	/* the special sequence to enable the extra buttons and the roller. */
	for (i = 0; i < nitems(rate1); ++i)
		if (set_mouse_sampling_rate(kbdc, rate1[i]) != rate1[i])
			return (FALSE);
	/* the device will give the genuine ID only after the above sequence */
	id = get_aux_id(kbdc);
	if (id != PSM_EXPLORER_ID)
		return (FALSE);

	if (arg == PROBE) {
		sc->hw.buttons = 5;	/* IntelliMouse Explorer XXX */
		sc->hw.hwid = id;
	}

	/*
	 * XXX: this is a kludge to fool some KVM switch products
	 * which think they are clever enough to know the 4-byte IntelliMouse
	 * protocol, and assume any other protocols use 3-byte packets.
	 * They don't convey 4-byte data packets from the IntelliMouse Explorer
	 * correctly to the host computer because of this!
	 * The following sequence is actually IntelliMouse's "wake up"
	 * sequence; it will make the KVM think the mouse is IntelliMouse
	 * when it is in fact IntelliMouse Explorer.
	 */
	for (i = 0; i < nitems(rate0); ++i)
		if (set_mouse_sampling_rate(kbdc, rate0[i]) != rate0[i])
			break;
	get_aux_id(kbdc);

	return (TRUE);
}