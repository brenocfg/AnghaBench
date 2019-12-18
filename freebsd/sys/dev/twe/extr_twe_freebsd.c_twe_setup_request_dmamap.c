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
struct twe_softc {int /*<<< orphan*/  twe_cmdphys; } ;
struct TYPE_3__ {int /*<<< orphan*/  ds_addr; } ;
typedef  TYPE_1__ bus_dma_segment_t ;

/* Variables and functions */
 int /*<<< orphan*/  debug_called (int) ; 

__attribute__((used)) static void
twe_setup_request_dmamap(void *arg, bus_dma_segment_t *segs, int nsegments, int error)
{
    struct twe_softc	*sc = (struct twe_softc *)arg;

    debug_called(4);

    /* command can't cross a page boundary */
    sc->twe_cmdphys = segs[0].ds_addr;
}