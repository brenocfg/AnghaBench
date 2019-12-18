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
 scalar_t__ EOF ; 
 int address ; 
 scalar_t__ getchar () ; 
 int skip ; 

__attribute__((used)) static void
noseek(void)
{
	int count;
	for (count = 0; count < skip; ++count)
		if (getchar() == EOF)
			break;
	address += count;
	skip -= count;
}