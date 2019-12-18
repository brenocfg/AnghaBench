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
 scalar_t__ OF_read (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int saved_char ; 
 int /*<<< orphan*/  stdin ; 

int
ofw_cons_poll()
{
	unsigned char ch;

	if (saved_char != -1)
		return 1;

	if (OF_read(stdin, &ch, 1) > 0) {
		saved_char = ch;
		return 1;
	}

	return 0;
}