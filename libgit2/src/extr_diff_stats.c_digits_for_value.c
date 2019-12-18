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

/* Variables and functions */

__attribute__((used)) static int digits_for_value(size_t val)
{
	int count = 1;
	size_t placevalue = 10;

	while (val >= placevalue) {
		++count;
		placevalue *= 10;
	}

	return count;
}