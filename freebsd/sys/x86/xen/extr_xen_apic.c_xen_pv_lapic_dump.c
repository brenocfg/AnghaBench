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
 int /*<<< orphan*/  printf (char*,int,char const*) ; 

__attribute__((used)) static void
xen_pv_lapic_dump(const char *str)
{

	printf("cpu%d %s XEN PV LAPIC\n", PCPU_GET(cpuid), str);
}