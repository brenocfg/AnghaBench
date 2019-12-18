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
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  read_inferior_memory (int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static int
amd64_breakpoint_at(CORE_ADDR pc)
{
	unsigned char c;

	read_inferior_memory(pc, &c, 1);
	if (c == 0xCC)
		return (1);

	return (0);
}