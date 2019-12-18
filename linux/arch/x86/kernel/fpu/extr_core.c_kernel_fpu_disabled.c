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
 int /*<<< orphan*/  in_kernel_fpu ; 
 int this_cpu_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool kernel_fpu_disabled(void)
{
	return this_cpu_read(in_kernel_fpu);
}