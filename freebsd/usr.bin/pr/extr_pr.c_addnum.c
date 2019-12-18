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
 char* digs ; 

void
addnum(char *buf, int wdth, int line)
{
	char *pt = buf + wdth;

	do {
		*--pt = digs[line % 10];
		line /= 10;
	} while (line && (pt > buf));

	/*
	 * pad with space as required
	 */
	while (pt > buf)
		*--pt = ' ';
}