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
typedef  int /*<<< orphan*/  vm_paddr_t ;
typedef  int /*<<< orphan*/  bus_size_t ;
typedef  TYPE_1__* bus_dma_tag_t ;
struct TYPE_4__ {int bounce_flags; } ;

/* Variables and functions */
 int BF_COULD_BOUNCE ; 
 int /*<<< orphan*/  _bus_dmamap_pagesneeded (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
bounce_bus_dma_id_mapped(bus_dma_tag_t dmat, vm_paddr_t buf, bus_size_t buflen)
{

	if ((dmat->bounce_flags & BF_COULD_BOUNCE) == 0)
		return (true);
	return (!_bus_dmamap_pagesneeded(dmat, buf, buflen, NULL));
}