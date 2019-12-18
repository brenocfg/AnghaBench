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
typedef  int /*<<< orphan*/  sli4_t ;
typedef  int int32_t ;

/* Variables and functions */
#define  SLI4_ASIC_TYPE_BE3 132 
#define  SLI4_ASIC_TYPE_CORSAIR 131 
#define  SLI4_ASIC_TYPE_LANCER 130 
#define  SLI4_ASIC_TYPE_LANCERG6 129 
#define  SLI4_ASIC_TYPE_SKYHAWK 128 
 int sli_get_asic_type (int /*<<< orphan*/ *) ; 

int32_t sli_link_is_configurable(sli4_t *sli)
{
	int32_t rc = 0;
	/*
	 * Link config works on: Skyhawk and Lancer
	 * Link config does not work on: LancerG6
	 */

	switch (sli_get_asic_type(sli)) {
	case SLI4_ASIC_TYPE_SKYHAWK:
	case SLI4_ASIC_TYPE_LANCER:
	case SLI4_ASIC_TYPE_CORSAIR:
		rc = 1;
		break;
	case SLI4_ASIC_TYPE_LANCERG6:
	case SLI4_ASIC_TYPE_BE3:
	default:
		rc = 0;
		break;
	}

	return rc;

}