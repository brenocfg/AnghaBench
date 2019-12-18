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
struct mly_softc {int /*<<< orphan*/  mly_mmbox_busaddr; } ;
struct TYPE_3__ {int /*<<< orphan*/  ds_addr; } ;
typedef  TYPE_1__ bus_dma_segment_t ;

/* Variables and functions */
 int /*<<< orphan*/  debug_called (int) ; 

__attribute__((used)) static void
mly_mmbox_map_helper(void *arg, bus_dma_segment_t *segs, int nseg, int error)
{
    struct mly_softc	*sc = (struct mly_softc *)arg;

    debug_called(1);

    sc->mly_mmbox_busaddr = segs->ds_addr;
}