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

void
poke(int *b, size_t index)
{
	size_t i;
	volatile int sum = 0;

	b[index] = 42;
	for (i = 0; i < 10; i++) 
		sum += b[i];
}