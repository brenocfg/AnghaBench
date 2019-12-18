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
ofw_cons_getchar()
{
	unsigned char ch = '\0';
	int l;

	if (saved_char != -1) {
		l = saved_char;
		saved_char = -1;
		return l;
	}

	/* At least since version 4.0.0, QEMU became bug-compatible
	 * with PowerVM's vty, by inserting a \0 after every \r.
	 * As this confuses loader's interpreter and as a \0 coming
	 * from the console doesn't seem reasonable, it's filtered here. */
	if (OF_read(stdin, &ch, 1) > 0 && ch != '\0')
		return (ch);

	return (-1);
}