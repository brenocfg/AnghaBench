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
struct regmap_mmio_context {scalar_t__ regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  writeb (unsigned int,scalar_t__) ; 

__attribute__((used)) static void regmap_mmio_write8(struct regmap_mmio_context *ctx,
				unsigned int reg,
				unsigned int val)
{
	writeb(val, ctx->regs + reg);
}