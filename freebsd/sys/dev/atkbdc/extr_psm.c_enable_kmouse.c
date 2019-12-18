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
typedef  int u_char ;
struct psm_softc {int /*<<< orphan*/  kbdc; } ;
typedef  enum probearg { ____Placeholder_probearg } probearg ;
typedef  int /*<<< orphan*/  KBDC ;

/* Variables and functions */
 int FALSE ; 
 int PSMD_RES_LOW ; 
 int TRUE ; 
 int /*<<< orphan*/  disable_aux_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  empty_aux_buffer (int /*<<< orphan*/ ,int) ; 
 int get_aux_id (int /*<<< orphan*/ ) ; 
 int get_mouse_status (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int) ; 
 int nitems (int*) ; 
 int set_mouse_resolution (int /*<<< orphan*/ ,int) ; 
 int set_mouse_sampling_rate (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
enable_kmouse(struct psm_softc *sc, enum probearg arg)
{
	static u_char rate[] = { 20, 60, 40, 20, 20, 60, 40, 20, 20 };
	KBDC kbdc = sc->kbdc;
	int status[3];
	int id1;
	int id2;
	int i;

	id1 = get_aux_id(kbdc);
	if (set_mouse_sampling_rate(kbdc, 10) != 10)
		return (FALSE);
	/*
	 * The device is now in the native mode? It returns a different
	 * ID value...
	 */
	id2 = get_aux_id(kbdc);
	if ((id1 == id2) || (id2 != 2))
		return (FALSE);

	if (set_mouse_resolution(kbdc, PSMD_RES_LOW) != PSMD_RES_LOW)
		return (FALSE);
#if PSM_DEBUG >= 2
	/* at this point, resolution is LOW, sampling rate is 10/sec */
	if (get_mouse_status(kbdc, status, 0, 3) < 3)
		return (FALSE);
#endif

	/*
	 * The special sequence to enable the third and fourth buttons.
	 * Otherwise they behave like the first and second buttons.
	 */
	for (i = 0; i < nitems(rate); ++i)
		if (set_mouse_sampling_rate(kbdc, rate[i]) != rate[i])
			return (FALSE);

	/*
	 * At this point, the device is using default resolution and
	 * sampling rate for the native mode.
	 */
	if (get_mouse_status(kbdc, status, 0, 3) < 3)
		return (FALSE);
	if ((status[1] == PSMD_RES_LOW) || (status[2] == rate[i - 1]))
		return (FALSE);

	/* the device appears be enabled by this sequence, diable it for now */
	disable_aux_dev(kbdc);
	empty_aux_buffer(kbdc, 5);

	return (TRUE);
}