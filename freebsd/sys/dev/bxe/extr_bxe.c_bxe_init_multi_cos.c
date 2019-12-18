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
typedef  int uint32_t ;
struct bxe_softc {int max_cos; int* prio_to_cos; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGW (struct bxe_softc*,char*,int,int,int) ; 
 int BXE_MAX_PRIORITY ; 

__attribute__((used)) static void
bxe_init_multi_cos(struct bxe_softc *sc)
{
    int pri, cos;

    uint32_t pri_map = 0; /* XXX change to user config */

    for (pri = 0; pri < BXE_MAX_PRIORITY; pri++) {
        cos = ((pri_map & (0xf << (pri * 4))) >> (pri * 4));
        if (cos < sc->max_cos) {
            sc->prio_to_cos[pri] = cos;
        } else {
            BLOGW(sc, "Invalid COS %d for priority %d "
                      "(max COS is %d), setting to 0\n",
                  cos, pri, (sc->max_cos - 1));
            sc->prio_to_cos[pri] = 0;
        }
    }
}