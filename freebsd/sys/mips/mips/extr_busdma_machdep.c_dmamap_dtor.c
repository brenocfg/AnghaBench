#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* bus_dmamap_t ;
struct TYPE_4__ {TYPE_1__* dmat; } ;
struct TYPE_3__ {int /*<<< orphan*/  map_count; } ;

/* Variables and functions */

__attribute__((used)) static void
dmamap_dtor(void *mem, int size, void *arg)
{
	bus_dmamap_t map;

	map = (bus_dmamap_t)mem;

	map->dmat->map_count--;
}