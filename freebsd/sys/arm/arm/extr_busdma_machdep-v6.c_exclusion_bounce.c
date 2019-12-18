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
typedef  TYPE_1__* bus_dma_tag_t ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int BUS_DMA_EXCL_BOUNCE ; 

__attribute__((used)) static __inline int
exclusion_bounce(bus_dma_tag_t dmat)
{

	return (dmat->flags & BUS_DMA_EXCL_BOUNCE);
}