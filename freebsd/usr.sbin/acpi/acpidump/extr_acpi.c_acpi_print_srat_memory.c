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
typedef  int uintmax_t ;
struct TYPE_3__ {int Flags; int ProximityDomain; scalar_t__ Length; scalar_t__ BaseAddress; } ;
typedef  TYPE_1__ ACPI_SRAT_MEM_AFFINITY ;

/* Variables and functions */
 int ACPI_SRAT_MEM_ENABLED ; 
 int ACPI_SRAT_MEM_HOT_PLUGGABLE ; 
 int ACPI_SRAT_MEM_NON_VOLATILE ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
acpi_print_srat_memory(ACPI_SRAT_MEM_AFFINITY *mp)
{

	printf("\tFlags={");
	if (mp->Flags & ACPI_SRAT_MEM_ENABLED)
		printf("ENABLED");
	else
		printf("DISABLED");
	if (mp->Flags & ACPI_SRAT_MEM_HOT_PLUGGABLE)
		printf(",HOT_PLUGGABLE");
	if (mp->Flags & ACPI_SRAT_MEM_NON_VOLATILE)
		printf(",NON_VOLATILE");
	printf("}\n");
	printf("\tBase Address=0x%016jx\n", (uintmax_t)mp->BaseAddress);
	printf("\tLength=0x%016jx\n", (uintmax_t)mp->Length);
	printf("\tProximity Domain=%d\n", mp->ProximityDomain);
}