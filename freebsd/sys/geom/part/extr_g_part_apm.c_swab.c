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

__attribute__((used)) static void
swab(char *buf, size_t bufsz)
{
	int i;
	char ch;

	for (i = 0; i < bufsz; i += 2) {
		ch = buf[i];
		buf[i] = buf[i + 1];
		buf[i + 1] = ch;
	}
}