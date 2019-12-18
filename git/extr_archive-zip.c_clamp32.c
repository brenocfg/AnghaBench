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
typedef  scalar_t__ const uintmax_t ;
typedef  scalar_t__ const uint32_t ;

/* Variables and functions */

__attribute__((used)) static uint32_t clamp32(uintmax_t n)
{
	const uintmax_t max = 0xffffffff;
	return (n < max) ? n : max;
}