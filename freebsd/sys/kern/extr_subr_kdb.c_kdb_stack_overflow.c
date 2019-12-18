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
 int PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpuid ; 

__attribute__((used)) static void
kdb_stack_overflow(volatile int *x)
{

	if (*x > 10000000)
		return;
	kdb_stack_overflow(x);
	*x += PCPU_GET(cpuid) / 1000000;
}