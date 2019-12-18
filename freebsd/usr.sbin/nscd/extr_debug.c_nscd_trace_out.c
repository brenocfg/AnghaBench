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
 int TRACE_WANTED ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int trace_level ; 

void
nscd_trace_out(const char *s, const char *f, int l)
{
	int i;

	--trace_level;
	if (trace_level < TRACE_WANTED)
	{
		for (i = 0; i < trace_level; ++i)
			printf("\t");

		printf("<= %s, %s: %d\n", s, f, l);
	}
}