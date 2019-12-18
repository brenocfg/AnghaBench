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
struct sunxi_rsb_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct sunxi_rsb_ctx*) ; 

__attribute__((used)) static void regmap_sunxi_rsb_free_ctx(void *context)
{
	struct sunxi_rsb_ctx *ctx = context;

	kfree(ctx);
}