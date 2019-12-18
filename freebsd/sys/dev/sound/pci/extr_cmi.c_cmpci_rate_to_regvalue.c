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
typedef  int u_int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEB (int /*<<< orphan*/ ) ; 
 int NUM_CMI_RATES ; 
 int* cmi_rates ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 

__attribute__((used)) static u_int32_t
cmpci_rate_to_regvalue(int rate)
{
	int i, r;

	for(i = 0; i < NUM_CMI_RATES - 1; i++) {
		if (rate < ((cmi_rates[i] + cmi_rates[i + 1]) / 2)) {
			break;
		}
	}

	DEB(printf("cmpci_rate_to_regvalue: %d -> %d\n", rate, cmi_rates[i]));

	r = ((i >> 1) | (i << 2)) & 0x07;
	return r;
}