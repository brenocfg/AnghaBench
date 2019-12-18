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

__attribute__((used)) static void trunc_nl(char *str)
{
	char *pos = str;
	while (*pos != '\0') {
		if (*pos == '\n') {
			*pos = '\0';
			break;
		}
		pos++;
	}
}