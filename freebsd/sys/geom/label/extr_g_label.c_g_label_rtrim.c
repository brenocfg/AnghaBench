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
typedef  size_t ptrdiff_t ;

/* Variables and functions */

void
g_label_rtrim(char *label, size_t size)
{
	ptrdiff_t i;

	for (i = size - 1; i >= 0; i--) {
		if (label[i] == '\0')
			continue;
		else if (label[i] == ' ')
			label[i] = '\0';
		else
			break;
	}
}