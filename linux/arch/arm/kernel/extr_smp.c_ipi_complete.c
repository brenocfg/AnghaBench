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
 int /*<<< orphan*/  complete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_completion ; 
 int /*<<< orphan*/  per_cpu (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void ipi_complete(unsigned int cpu)
{
	complete(per_cpu(cpu_completion, cpu));
}