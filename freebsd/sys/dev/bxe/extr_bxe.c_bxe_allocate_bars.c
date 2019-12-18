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
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int /*<<< orphan*/  u_int ;
struct bxe_softc {TYPE_1__* bar; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {scalar_t__ kva; int /*<<< orphan*/ * resource; int /*<<< orphan*/  handle; int /*<<< orphan*/  tag; int /*<<< orphan*/  rid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGI (struct bxe_softc*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MAX_BARS ; 
 int /*<<< orphan*/  PCIR_BAR (int) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_start (int /*<<< orphan*/ *) ; 
 scalar_t__ rman_get_virtual (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
bxe_allocate_bars(struct bxe_softc *sc)
{
    u_int flags;
    int i;

    memset(sc->bar, 0, sizeof(sc->bar));

    for (i = 0; i < MAX_BARS; i++) {

        /* memory resources reside at BARs 0, 2, 4 */
        /* Run `pciconf -lb` to see mappings */
        if ((i != 0) && (i != 2) && (i != 4)) {
            continue;
        }

        sc->bar[i].rid = PCIR_BAR(i);

        flags = RF_ACTIVE;
        if (i == 0) {
            flags |= RF_SHAREABLE;
        }

        if ((sc->bar[i].resource =
             bus_alloc_resource_any(sc->dev,
                                    SYS_RES_MEMORY,
                                    &sc->bar[i].rid,
                                    flags)) == NULL) {
            return (0);
        }

        sc->bar[i].tag    = rman_get_bustag(sc->bar[i].resource);
        sc->bar[i].handle = rman_get_bushandle(sc->bar[i].resource);
        sc->bar[i].kva    = (vm_offset_t)rman_get_virtual(sc->bar[i].resource);

        BLOGI(sc, "PCI BAR%d [%02x] memory allocated: %#jx-%#jx (%jd) -> %#jx\n",
              i, PCIR_BAR(i),
              rman_get_start(sc->bar[i].resource),
              rman_get_end(sc->bar[i].resource),
              rman_get_size(sc->bar[i].resource),
              (uintmax_t)sc->bar[i].kva);
    }

    return (0);
}