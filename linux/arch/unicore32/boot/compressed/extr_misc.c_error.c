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
 int /*<<< orphan*/  arch_decomp_error (char*) ; 
 int /*<<< orphan*/  arch_decomp_puts (char*) ; 

void error(char *x)
{
	arch_decomp_puts("\n\n");
	arch_decomp_puts(x);
	arch_decomp_puts("\n\n -- System halted");

	arch_decomp_error(x);

	for (;;)
		; /* Halt */
}