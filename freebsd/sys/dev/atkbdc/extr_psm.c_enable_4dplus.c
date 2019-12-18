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
struct TYPE_2__ {int buttons; int hwid; } ;
struct psm_softc {TYPE_1__ hw; int /*<<< orphan*/  kbdc; } ;
typedef  enum probearg { ____Placeholder_probearg } probearg ;
typedef  int /*<<< orphan*/  KBDC ;

/* Variables and functions */
 int FALSE ; 
 int PROBE ; 
#define  PSM_4DPLUS_ID 129 
#define  PSM_4DPLUS_RFSW35_ID 128 
 int TRUE ; 
 int get_aux_id (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
enable_4dplus(struct psm_softc *sc, enum probearg arg)
{
	KBDC kbdc = sc->kbdc;
	int id;

	/*
	 * enable_4dmouse() already issued the following ID sequence...
	static u_char rate[] = { 200, 100, 80, 60, 40, 20 };
	int i;

	for (i = 0; i < sizeof(rate)/sizeof(rate[0]); ++i)
		if (set_mouse_sampling_rate(kbdc, rate[i]) != rate[i])
			return (FALSE);
	*/

	id = get_aux_id(kbdc);
	switch (id) {
	case PSM_4DPLUS_ID:
		break;
	case PSM_4DPLUS_RFSW35_ID:
		break;
	default:
		return (FALSE);
	}

	if (arg == PROBE) {
		sc->hw.buttons = (id == PSM_4DPLUS_ID) ? 4 : 3;
		sc->hw.hwid = id;
	}

	return (TRUE);
}