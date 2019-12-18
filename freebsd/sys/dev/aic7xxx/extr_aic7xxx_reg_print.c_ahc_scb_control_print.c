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
typedef  int /*<<< orphan*/  u_int ;

/* Variables and functions */
 int /*<<< orphan*/  SCB_CONTROL_parse_table ; 
 int ahc_print_register (int /*<<< orphan*/ ,int,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
ahc_scb_control_print(u_int regvalue, u_int *cur_col, u_int wrap)
{
	return (ahc_print_register(SCB_CONTROL_parse_table, 8, "SCB_CONTROL",
	    0xb8, regvalue, cur_col, wrap));
}