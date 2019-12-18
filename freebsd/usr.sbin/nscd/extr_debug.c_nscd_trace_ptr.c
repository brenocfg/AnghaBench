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
nscd_trace_ptr(const char *desc, const void *p, const char *f, int l)
{
	int i;

	if (trace_level < TRACE_WANTED)
	{
		for (i = 0; i < trace_level - 1; ++i)
			printf("\t");

		printf("= PTR %s: %p, %s: %d\n", desc, p, f, l);
	}
}