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
 int /*<<< orphan*/  failure (char*,int) ; 

__attribute__((used)) static int
int_in_list(int i, const int *l, size_t n)
{
	while (n-- > 0)
		if (*l++ == i)
			return (1);
	failure("%d", i);
	return (0);
}