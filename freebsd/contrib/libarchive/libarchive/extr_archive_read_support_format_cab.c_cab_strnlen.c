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
typedef  int ssize_t ;

/* Variables and functions */

__attribute__((used)) static ssize_t
cab_strnlen(const unsigned char *p, size_t maxlen)
{
	size_t i;

	for (i = 0; i <= maxlen; i++) {
		if (p[i] == 0)
			break;
	}
	if (i > maxlen)
		return (-1);/* invalid */
	return ((ssize_t)i);
}