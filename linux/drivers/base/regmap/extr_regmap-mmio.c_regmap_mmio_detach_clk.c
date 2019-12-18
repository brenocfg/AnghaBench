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
struct regmap_mmio_context {int attached_clk; int /*<<< orphan*/ * clk; } ;
struct regmap {struct regmap_mmio_context* bus_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ *) ; 

void regmap_mmio_detach_clk(struct regmap *map)
{
	struct regmap_mmio_context *ctx = map->bus_context;

	clk_unprepare(ctx->clk);

	ctx->attached_clk = false;
	ctx->clk = NULL;
}