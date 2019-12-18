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
 int /*<<< orphan*/  DUMP_ALL ; 
 int /*<<< orphan*/  DUMP_ORIG ; 
 int /*<<< orphan*/  ftrace_dump (int /*<<< orphan*/ ) ; 
 int inchar () ; 

__attribute__((used)) static void dump_tracing(void)
{
	int c;

	c = inchar();
	if (c == 'c')
		ftrace_dump(DUMP_ORIG);
	else
		ftrace_dump(DUMP_ALL);
}