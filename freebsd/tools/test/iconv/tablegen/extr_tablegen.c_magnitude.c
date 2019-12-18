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

__attribute__((used)) static int
magnitude(const uint32_t p)
{

	if (p >> 8 == 0)
		return (1);
	else if (p >> 16 == 0)
		return (2);
	else
		return (p >> 24 == 0 ? 3 : 4);
}