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
 int PSMD_RES_LOW ; 
 int TRUE ; 
 int /*<<< orphan*/  mouse_id_proc1 (int /*<<< orphan*/ ,int,int,int*) ; 
 int set_mouse_sampling_rate (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
enable_aglide(struct psm_softc *sc, enum probearg arg)
{
	KBDC kbdc = sc->kbdc;
	int status[3];

	/*
	 * The special sequence to obtain ALPS GlidePoint specific
	 * information. Immediately after this sequence, status bytes will
	 * contain something interesting.
	 * NOTE: ALPS produces several models of GlidePoint. Some of those
	 * do not respond to this sequence, thus, cannot be detected this way.
	 */
	if (set_mouse_sampling_rate(kbdc, 100) != 100)
		return (FALSE);
	if (!mouse_id_proc1(kbdc, PSMD_RES_LOW, 2, status))
		return (FALSE);
	if ((status[1] == PSMD_RES_LOW) || (status[2] == 100))
		return (FALSE);
	return (TRUE);
}