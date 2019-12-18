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
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static void aggregate_32bit(uint32_t * dest, uint32_t val)
{
	if (((*dest) + val) < (*dest))
		(*dest) = 0xffffffff;
	else
		(*dest) = (*dest) + val;
}