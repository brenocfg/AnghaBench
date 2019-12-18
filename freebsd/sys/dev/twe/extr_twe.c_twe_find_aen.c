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
typedef  scalar_t__ u_int16_t ;
struct twe_softc {int twe_aen_tail; int twe_aen_head; scalar_t__* twe_aen_queue; } ;

/* Variables and functions */
 int TWE_Q_LENGTH ; 

__attribute__((used)) static int
twe_find_aen(struct twe_softc *sc, u_int16_t aen)
{
    int		i, missing;

    missing = 1;
    for (i = sc->twe_aen_tail; (i != sc->twe_aen_head) && missing; i = (i + 1) % TWE_Q_LENGTH) {
	if (sc->twe_aen_queue[i] == aen)
	    missing = 0;
    }
    return(missing);
}