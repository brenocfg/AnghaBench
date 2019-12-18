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
struct bxe_softc {TYPE_1__* bar; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * resource; int /*<<< orphan*/  rid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGD (struct bxe_softc*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBG_LOAD ; 
 int MAX_BARS ; 
 int /*<<< orphan*/  PCIR_BAR (int) ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bxe_deallocate_bars(struct bxe_softc *sc)
{
    int i;

    for (i = 0; i < MAX_BARS; i++) {
        if (sc->bar[i].resource != NULL) {
            bus_release_resource(sc->dev,
                                 SYS_RES_MEMORY,
                                 sc->bar[i].rid,
                                 sc->bar[i].resource);
            BLOGD(sc, DBG_LOAD, "Released PCI BAR%d [%02x] memory\n",
                  i, PCIR_BAR(i));
        }
    }
}