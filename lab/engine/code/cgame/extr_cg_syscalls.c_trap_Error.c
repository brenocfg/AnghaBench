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
 int /*<<< orphan*/  CG_ERROR ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  syscall (int /*<<< orphan*/ ,char const*) ; 

void trap_Error(const char *fmt)
{
	syscall(CG_ERROR, fmt);
	// shut up GCC warning about returning functions, because we know better
	exit(1);
}