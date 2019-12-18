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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 scalar_t__ ID_AA64MMFR1_PAN_NONE ; 
 scalar_t__ ID_AA64MMFR1_PAN_VAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  READ_SPECIALREG (int /*<<< orphan*/ ) ; 
 int has_pan ; 
 int /*<<< orphan*/  id_aa64mmfr1_el1 ; 

__attribute__((used)) static void
pan_setup(void)
{
	uint64_t id_aa64mfr1;

	id_aa64mfr1 = READ_SPECIALREG(id_aa64mmfr1_el1);
	if (ID_AA64MMFR1_PAN_VAL(id_aa64mfr1) != ID_AA64MMFR1_PAN_NONE)
		has_pan = 1;
}