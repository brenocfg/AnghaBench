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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 scalar_t__ snprintf (char*,size_t,char*,char*,int /*<<< orphan*/  const) ; 

int sprint_uint8_arr(char *buf, size_t size,
		     const uint8_t * arr, size_t len)
{
	int n;
	unsigned int i;
	for (i = 0, n = 0; i < len; i++) {
		n += snprintf(buf + n, size - n, "%s%u", i == 0 ? "" : ",",
			      arr[i]);
		if (n >= size)
			break;
	}
	return n;
}