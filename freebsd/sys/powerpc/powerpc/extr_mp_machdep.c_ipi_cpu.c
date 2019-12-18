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
typedef  int /*<<< orphan*/  u_int ;

/* Variables and functions */
 int /*<<< orphan*/ * cpuid_to_pcpu ; 
 int /*<<< orphan*/  ipi_send (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ipi_cpu(int cpu, u_int ipi)
{

	ipi_send(cpuid_to_pcpu[cpu], ipi);
}