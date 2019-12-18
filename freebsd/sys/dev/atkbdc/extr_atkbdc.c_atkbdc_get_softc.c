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
typedef  int /*<<< orphan*/  atkbdc_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/ ** atkbdc_softc ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int) ; 
 int nitems (int /*<<< orphan*/ **) ; 

atkbdc_softc_t
*atkbdc_get_softc(int unit)
{
	atkbdc_softc_t *sc;

	if (unit >= nitems(atkbdc_softc))
		return NULL;
	sc = atkbdc_softc[unit];
	if (sc == NULL) {
		sc = atkbdc_softc[unit]
		   = malloc(sizeof(*sc), M_DEVBUF, M_NOWAIT | M_ZERO);
		if (sc == NULL)
			return NULL;
	}
	return sc;
}