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
struct TYPE_2__ {int /*<<< orphan*/  (* early_clock_source_init ) () ;} ;

/* Variables and functions */
 int MTX_NOPROFILE ; 
 int MTX_SPIN ; 
 int /*<<< orphan*/  clock_lock ; 
 TYPE_1__ init_ops ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 () ; 

void
clock_init(void)
{
	/* Init the clock lock */
	mtx_init(&clock_lock, "clk", NULL, MTX_SPIN | MTX_NOPROFILE);
	/* Init the clock in order to use DELAY */
	init_ops.early_clock_source_init();
}