#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* desc; int metal_rev; } ;
struct TYPE_3__ {char* desc; scalar_t__ hw_rev; } ;

/* Variables and functions */
 scalar_t__ AML_SOC_HW_REV_M8 ; 
 TYPE_2__* aml8726_m8_soc_rev ; 
 TYPE_1__* aml8726_soc_desc ; 
 scalar_t__ aml8726_soc_hw_rev ; 
 int aml8726_soc_metal_rev ; 
 int /*<<< orphan*/  panic (char*,scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
aml8726_identify_announce_soc(void *dummy)
{
	int i;

	for (i = 0; aml8726_soc_desc[i].desc; i++)
		if (aml8726_soc_desc[i].hw_rev == aml8726_soc_hw_rev)
			break;

	if (aml8726_soc_desc[i].desc == NULL)
		panic("Amlogic unknown aml8726 SoC %#x\n", aml8726_soc_hw_rev);

	printf("Amlogic %s SoC", aml8726_soc_desc[i].desc);

	if (aml8726_soc_hw_rev == AML_SOC_HW_REV_M8) {
		for (i = 0; aml8726_m8_soc_rev[i].desc; i++)
			if (aml8726_m8_soc_rev[i].metal_rev ==
			    aml8726_soc_metal_rev)
				break;

		if (aml8726_m8_soc_rev[i].desc == NULL)
			printf(", unknown rev %#x", aml8726_soc_metal_rev);
		else
			printf(", rev %s", aml8726_m8_soc_rev[i].desc);
	}

	printf("\n");
}