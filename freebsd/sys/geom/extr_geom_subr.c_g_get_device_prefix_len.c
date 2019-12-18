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
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static int
g_get_device_prefix_len(const char *name)
{
	int len;

	if (strncmp(name, "ada", 3) == 0)
		len = 3;
	else if (strncmp(name, "ad", 2) == 0)
		len = 2;
	else
		return (0);
	if (name[len] < '0' || name[len] > '9')
		return (0);
	do {
		len++;
	} while (name[len] >= '0' && name[len] <= '9');
	return (len);
}