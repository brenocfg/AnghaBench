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
typedef  int uintmax_t ;
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static void
acpi_print_io_apic(uint32_t apic_id, uint32_t int_base, uint64_t apic_addr)
{

	printf("\tAPIC ID=%d\n", apic_id);
	printf("\tINT BASE=%d\n", int_base);
	printf("\tADDR=0x%016jx\n", (uintmax_t)apic_addr);
}