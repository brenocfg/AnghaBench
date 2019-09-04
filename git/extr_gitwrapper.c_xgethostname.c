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
 int gethostname (char*,size_t) ; 

int xgethostname(char *buf, size_t len)
{
	/*
	 * If the full hostname doesn't fit in buf, POSIX does not
	 * specify whether the buffer will be null-terminated, so to
	 * be safe, do it ourselves.
	 */
	int ret = gethostname(buf, len);
	if (!ret)
		buf[len - 1] = 0;
	return ret;
}