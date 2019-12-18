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
 int /*<<< orphan*/  at93c_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int EEPROMWrite(unsigned int pos, unsigned char *data, int len)
{
	int i;

	for (i = 0; i < len; i++)
		at93c_write(pos++, *data++);

	return 0;
}