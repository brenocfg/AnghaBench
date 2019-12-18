#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int flags; int asic_revision; } ;
typedef  TYPE_1__* POCE_SOFTC ;

/* Variables and functions */
 int FALSE ; 
 int OCE_FLAGS_BE3 ; 
 int TRUE ; 

__attribute__((used)) static int 
is_be3_a1(POCE_SOFTC sc)
{
	if((sc->flags & OCE_FLAGS_BE3)  && ((sc->asic_revision & 0xFF) < 2)) {
		return TRUE;
	}
	return FALSE;
}