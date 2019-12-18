#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  dma; } ;
typedef  TYPE_1__ oce_ring_buffer_t ;
typedef  int /*<<< orphan*/  POCE_SOFTC ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oce_dma_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
oce_destroy_ring_buffer(POCE_SOFTC sc, oce_ring_buffer_t *ring)
{
	oce_dma_free(sc, &ring->dma);
	free(ring, M_DEVBUF);
}