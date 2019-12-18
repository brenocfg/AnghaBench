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
struct omap_dmadev {scalar_t__ base; struct omap_dma_reg* reg_map; } ;
struct omap_dma_reg {scalar_t__ offset; int /*<<< orphan*/  type; int /*<<< orphan*/  stride; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_dma_write (unsigned int,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void omap_dma_glbl_write(struct omap_dmadev *od, unsigned reg, unsigned val)
{
	const struct omap_dma_reg *r = od->reg_map + reg;

	WARN_ON(r->stride);

	omap_dma_write(val, r->type, od->base + r->offset);
}