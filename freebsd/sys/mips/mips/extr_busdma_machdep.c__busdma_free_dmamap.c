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
typedef  TYPE_1__* bus_dmamap_t ;
struct TYPE_4__ {int /*<<< orphan*/  slist; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_BUSDMA ; 
 int /*<<< orphan*/  dmamap_zone ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static __inline void
_busdma_free_dmamap(bus_dmamap_t map)
{

	free(map->slist, M_BUSDMA);
	uma_zfree(dmamap_zone, map);
}