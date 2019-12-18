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
struct pt_errata {int bdm70; int bdm64; int skd007; int skd022; int skd010; int skl014; int skl168; int apl12; int apl11; } ;
struct pt_cpu {scalar_t__ vendor; int family; int /*<<< orphan*/  model; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct pt_errata*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pcv_intel ; 
 int pte_bad_cpu ; 
 int pte_invalid ; 

int pt_cpu_errata(struct pt_errata *errata, const struct pt_cpu *cpu)
{
	if (!errata || !cpu)
		return -pte_invalid;

	memset(errata, 0, sizeof(*errata));

	/* We don't know about others. */
	if (cpu->vendor != pcv_intel)
		return -pte_bad_cpu;

	switch (cpu->family) {
	case 0x6:
		switch (cpu->model) {
		case 0x3d:
		case 0x47:
		case 0x4f:
		case 0x56:
			errata->bdm70 = 1;
			errata->bdm64 = 1;
			return 0;

		case 0x4e:
		case 0x5e:
		case 0x8e:
		case 0x9e:
			errata->bdm70 = 1;
			errata->skd007 = 1;
			errata->skd022 = 1;
			errata->skd010 = 1;
			errata->skl014 = 1;
			errata->skl168 = 1;
			return 0;

		case 0x55:
		case 0x66:
		case 0x7d:
		case 0x7e:
			errata->bdm70 = 1;
			errata->skl014 = 1;
			errata->skd022 = 1;
			return 0;

		case 0x5c:
		case 0x5f:
			errata->apl12 = 1;
			errata->apl11 = 1;
			return 0;

		case 0x7a:
		case 0x86:
			errata->apl11 = 1;
			return 0;
		}
		break;
	}

	return -pte_bad_cpu;
}