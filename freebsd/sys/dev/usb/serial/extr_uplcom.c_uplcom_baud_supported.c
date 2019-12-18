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
 int N_UPLCOM_RATES ; 
 unsigned int* uplcom_rates ; 

__attribute__((used)) static int
uplcom_baud_supported(unsigned int speed)
{
	int i;
	for (i = 0; i < N_UPLCOM_RATES; i++) {
		if (uplcom_rates[i] == speed)
			return 1;
	}
	return 0;
}