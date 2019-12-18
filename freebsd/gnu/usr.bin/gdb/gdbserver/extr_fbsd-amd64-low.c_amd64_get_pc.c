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
typedef  unsigned long CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  collect_register_by_name (char*,unsigned long*) ; 
 scalar_t__ debug_threads ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,unsigned long) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static CORE_ADDR
amd64_get_pc(void)
{
	unsigned long pc;

	collect_register_by_name("rip", &pc);

	if (debug_threads)
		fprintf(stderr, "stop pc (before any decrement) is %016lx\n", pc);

	return (pc);
}