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
struct bus_dma_tag_common {TYPE_1__* impl; } ;
typedef  scalar_t__ bus_dma_tag_t ;
struct TYPE_2__ {int (* tag_destroy ) (scalar_t__) ;} ;

/* Variables and functions */
 int stub1 (scalar_t__) ; 

int
bus_dma_tag_destroy(bus_dma_tag_t dmat)
{
	struct bus_dma_tag_common *tc;

	tc = (struct bus_dma_tag_common *)dmat;
	return (tc->impl->tag_destroy(dmat));
}