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
typedef  int uint8_t ;

/* Variables and functions */
 int OCS_SERVICE_PARMS_LENGTH ; 
 int /*<<< orphan*/  sparms_cmp_mask ; 

int
ocs_sparm_cmp(uint8_t *sp1, uint8_t *sp2)
{
	int i;
	int v;
	uint8_t *sp3 = (uint8_t*) &sparms_cmp_mask;

	for (i = 0; i < OCS_SERVICE_PARMS_LENGTH; i ++) {
		v = ((int)(sp1[i] & sp3[i])) - ((int)(sp2[i] & sp3[i]));
		if (v) {
			break;
		}
	}
	return v;
}