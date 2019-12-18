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
 int /*<<< orphan*/  write (int,char*,int) ; 

__attribute__((used)) static void
write_num(int val)
{
	char buf[20];
	int i;

	for (i = sizeof buf; --i >= 0;) {
		buf[i] = '0' + val % 10;
		val /= 10;
		if (val == 0) {
			write(2, buf + i, sizeof buf - i);
			return;
		}
	}
	write(2, "overflow", 8);
}