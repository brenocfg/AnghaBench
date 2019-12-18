#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct omap_sg {size_t en; size_t fn; } ;

/* Variables and functions */

__attribute__((used)) static size_t omap_dma_sg_size(struct omap_sg *sg)
{
	return sg->en * sg->fn;
}