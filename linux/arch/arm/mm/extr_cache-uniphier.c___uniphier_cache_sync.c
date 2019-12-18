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
struct uniphier_cache_data {scalar_t__ op_base; } ;

/* Variables and functions */
 scalar_t__ UNIPHIER_SSCOPE ; 
 int /*<<< orphan*/  UNIPHIER_SSCOPE_CM_SYNC ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void __uniphier_cache_sync(struct uniphier_cache_data *data)
{
	/* This sequence need not be atomic.  Do not disable IRQ. */
	writel_relaxed(UNIPHIER_SSCOPE_CM_SYNC,
		       data->op_base + UNIPHIER_SSCOPE);
	/* need a read back to confirm */
	readl_relaxed(data->op_base + UNIPHIER_SSCOPE);
}