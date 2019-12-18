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
struct ps3_dma_region {TYPE_1__* region_ops; } ;
struct TYPE_2__ {int (* free ) (struct ps3_dma_region*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int stub1 (struct ps3_dma_region*) ; 

int ps3_dma_region_free(struct ps3_dma_region *r)
{
	BUG_ON(!r);
	BUG_ON(!r->region_ops);
	BUG_ON(!r->region_ops->free);
	return r->region_ops->free(r);
}