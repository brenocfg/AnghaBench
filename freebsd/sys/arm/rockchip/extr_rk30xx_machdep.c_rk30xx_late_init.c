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
typedef  int /*<<< orphan*/  platform_t ;

/* Variables and functions */
 int CPU_CONTROL_DC_ENABLE ; 
 int CPU_CONTROL_IC_ENABLE ; 
 int /*<<< orphan*/  cpufunc_control (int,int) ; 

__attribute__((used)) static void
rk30xx_late_init(platform_t plat)
{

	/* Enable cache */
	cpufunc_control(CPU_CONTROL_DC_ENABLE|CPU_CONTROL_IC_ENABLE,
	    CPU_CONTROL_DC_ENABLE|CPU_CONTROL_IC_ENABLE);
}