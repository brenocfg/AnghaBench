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
 int /*<<< orphan*/  dump_linkwidth (char*,int,int) ; 

void mad_dump_linkwidthen(char *buf, int bufsz, void *val, int valsz)
{
	int width = *(int *)val;

	dump_linkwidth(buf, bufsz, width);
}