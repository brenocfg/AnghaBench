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
 int /*<<< orphan*/  diff_output (char*,...) ; 

__attribute__((used)) static void
range(int a, int b, const char *separator)
{
	diff_output("%d", a > b ? b : a);
	if (a < b)
		diff_output("%s%d", separator, b);
}