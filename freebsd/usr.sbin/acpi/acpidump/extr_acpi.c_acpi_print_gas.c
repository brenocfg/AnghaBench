#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int uint16_t ;
typedef  int u_int ;
struct TYPE_3__ {int SpaceId; int BitWidth; int Address; int BitOffset; } ;
typedef  TYPE_1__ ACPI_GENERIC_ADDRESS ;

/* Variables and functions */
#define  ACPI_GAS_CMOS 136 
#define  ACPI_GAS_DATATABLE 135 
#define  ACPI_GAS_EMBEDDED 134 
#define  ACPI_GAS_FIXED 133 
#define  ACPI_GAS_IO 132 
#define  ACPI_GAS_MEMORY 131 
#define  ACPI_GAS_PCI 130 
#define  ACPI_GAS_PCIBAR 129 
#define  ACPI_GAS_SMBUS 128 
 int /*<<< orphan*/  printf (char*,int,...) ; 

__attribute__((used)) static void
acpi_print_gas(ACPI_GENERIC_ADDRESS *gas)
{
	switch(gas->SpaceId) {
	case ACPI_GAS_MEMORY:
		if (gas->BitWidth <= 32)
			printf("0x%08x:%u[%u] (Memory)",
			    (u_int)gas->Address, gas->BitOffset,
			    gas->BitWidth);
		else
			printf("0x%016jx:%u[%u] (Memory)",
			    (uintmax_t)gas->Address, gas->BitOffset,
			    gas->BitWidth);
		break;
	case ACPI_GAS_IO:
		printf("0x%02x:%u[%u] (IO)", (u_int)gas->Address,
		    gas->BitOffset, gas->BitWidth);
		break;
	case ACPI_GAS_PCI:
		printf("%x:%x+0x%x (PCI)", (uint16_t)(gas->Address >> 32),
		       (uint16_t)((gas->Address >> 16) & 0xffff),
		       (uint16_t)gas->Address);
		break;
	/* XXX How to handle these below? */
	case ACPI_GAS_EMBEDDED:
		printf("0x%x:%u[%u] (EC)", (uint16_t)gas->Address,
		       gas->BitOffset, gas->BitWidth);
		break;
	case ACPI_GAS_SMBUS:
		printf("0x%x:%u[%u] (SMBus)", (uint16_t)gas->Address,
		       gas->BitOffset, gas->BitWidth);
		break;
	case ACPI_GAS_CMOS:
	case ACPI_GAS_PCIBAR:
	case ACPI_GAS_DATATABLE:
	case ACPI_GAS_FIXED:
	default:
		printf("0x%016jx (?)", (uintmax_t)gas->Address);
		break;
	}
}