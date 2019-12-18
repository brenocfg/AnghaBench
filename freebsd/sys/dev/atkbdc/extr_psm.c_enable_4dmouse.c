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
 int PSM_4DMOUSE_ID ; 
 int TRUE ; 
 int get_aux_id (int /*<<< orphan*/ ) ; 
 int nitems (int*) ; 
 int set_mouse_sampling_rate (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
enable_4dmouse(struct psm_softc *sc, enum probearg arg)
{
	static u_char rate[] = { 200, 100, 80, 60, 40, 20 };
	KBDC kbdc = sc->kbdc;
	int id;
	int i;

	for (i = 0; i < nitems(rate); ++i)
		if (set_mouse_sampling_rate(kbdc, rate[i]) != rate[i])
			return (FALSE);
	id = get_aux_id(kbdc);
	/*
	 * WinEasy 4D, 4 Way Scroll 4D: 6
	 * Cable-Free 4D: 8 (4DPLUS)
	 * WinBest 4D+, 4 Way Scroll 4D+: 8 (4DPLUS)
	 */
	if (id != PSM_4DMOUSE_ID)
		return (FALSE);

	if (arg == PROBE) {
		sc->hw.buttons = 3;	/* XXX some 4D mice have 4? */
		sc->hw.hwid = id;
	}

	return (TRUE);
}