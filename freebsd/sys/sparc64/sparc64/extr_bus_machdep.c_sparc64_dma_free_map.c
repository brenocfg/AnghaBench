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
typedef  int /*<<< orphan*/  bus_dmamap_t ;
typedef  TYPE_1__* bus_dma_tag_t ;
struct TYPE_3__ {int /*<<< orphan*/  dt_map_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
sparc64_dma_free_map(bus_dma_tag_t dmat, bus_dmamap_t map)
{

	free(map, M_DEVBUF);
	dmat->dt_map_count--;
}