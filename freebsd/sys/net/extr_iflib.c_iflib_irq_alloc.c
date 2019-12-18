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
typedef  int /*<<< orphan*/  if_irq_t ;
typedef  int /*<<< orphan*/  if_ctx_t ;
typedef  int /*<<< orphan*/  driver_intr_t ;
typedef  int /*<<< orphan*/  driver_filter_t ;

/* Variables and functions */
 int _iflib_irq_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,char const*) ; 

int
iflib_irq_alloc(if_ctx_t ctx, if_irq_t irq, int rid,
		driver_filter_t filter, void *filter_arg, driver_intr_t handler, void *arg, const char *name)
{

	return (_iflib_irq_alloc(ctx, irq, rid, filter, handler, arg, name));
}