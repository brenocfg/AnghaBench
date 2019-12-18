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
struct psm_softc {int /*<<< orphan*/  kbdc; } ;
typedef  enum probearg { ____Placeholder_probearg } probearg ;
typedef  int /*<<< orphan*/  KBDC ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  PSMD_RES_HIGH ; 
 int TRUE ; 
 int /*<<< orphan*/  mouse_id_proc1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static int
enable_gmouse(struct psm_softc *sc, enum probearg arg)
{
	KBDC kbdc = sc->kbdc;
	int status[3];

	/*
	 * The special sequence to enable the middle, "rubber" button.
	 * Immediately after this sequence check status bytes.
	 * if the mouse is NetMouse, NetMouse Pro, or ASCII MIE Mouse,
	 * the second and the third bytes are '3' and 'U'.
	 * NOTE: NetMouse reports that it has three buttons although it has
	 * two buttons and a rubber button. NetMouse Pro and MIE Mouse
	 * say they have three buttons too and they do have a button on the
	 * side...
	 */
	if (!mouse_id_proc1(kbdc, PSMD_RES_HIGH, 1, status))
		return (FALSE);
	if ((status[1] != '3') || (status[2] != 'U'))
		return (FALSE);
	return (TRUE);
}