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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  fast_dll_ctrl; } ;

/* Variables and functions */
 TYPE_1__ mem_timings ; 

__attribute__((used)) static u32 omap2xxx_sdrc_get_fast_dll_ctrl(void)
{
	return mem_timings.fast_dll_ctrl;
}