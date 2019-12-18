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
struct TYPE_2__ {int buttons; } ;
struct psm_softc {TYPE_1__ hw; int /*<<< orphan*/  kbdc; } ;
typedef  enum probearg { ____Placeholder_probearg } probearg ;
typedef  int /*<<< orphan*/  KBDC ;

/* Variables and functions */
 int FALSE ; 
 int PROBE ; 
 int /*<<< orphan*/  PSMD_RES_HIGH ; 
 int TRUE ; 
 int /*<<< orphan*/  mouse_id_proc1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static int
enable_groller(struct psm_softc *sc, enum probearg arg)
{
	KBDC kbdc = sc->kbdc;
	int status[3];

	/*
	 * The special sequence to enable the fourth button and the
	 * roller. Immediately after this sequence check status bytes.
	 * if the mouse is NetScroll, the second and the third bytes are
	 * '3' and 'D'.
	 */

	/*
	 * If the mouse is an ordinary PS/2 mouse, the status bytes should
	 * look like the following.
	 *
	 * byte 1 bit 7 always 0
	 *        bit 6 stream mode (0)
	 *        bit 5 disabled (0)
	 *        bit 4 1:1 scaling (0)
	 *        bit 3 always 0
	 *        bit 0-2 button status
	 * byte 2 resolution (PSMD_RES_HIGH)
	 * byte 3 report rate (?)
	 */

	if (!mouse_id_proc1(kbdc, PSMD_RES_HIGH, 1, status))
		return (FALSE);
	if ((status[1] != '3') || (status[2] != 'D'))
		return (FALSE);
	/* FIXME: SmartScroll Mouse has 5 buttons! XXX */
	if (arg == PROBE)
		sc->hw.buttons = 4;
	return (TRUE);
}