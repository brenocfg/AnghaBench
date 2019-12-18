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
typedef  int u_int32_t ;

/* Variables and functions */

u_int32_t
extract_field(u_int32_t value, u_int32_t base, u_int32_t width)
{
	u_int32_t mask = (1 << width) - 1;
	return ((value >> base) & mask);
}