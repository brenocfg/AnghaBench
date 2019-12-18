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
typedef  int u8 ;
typedef  int u32 ;

/* Variables and functions */
 int calculate_ecc (int,int) ; 
 int syndrome_from_bit (int) ; 

__attribute__((used)) static void sbe_ecc_decode(u32 cap_high, u32 cap_low, u32 cap_ecc,
		       int *bad_data_bit, int *bad_ecc_bit)
{
	int i;
	u8 syndrome;

	*bad_data_bit = -1;
	*bad_ecc_bit = -1;

	/*
	 * Calculate the ECC of the captured data and XOR it with the captured
	 * ECC to find an ECC syndrome value we can search for
	 */
	syndrome = calculate_ecc(cap_high, cap_low) ^ cap_ecc;

	/* Check if a data line is stuck... */
	for (i = 0; i < 64; i++) {
		if (syndrome == syndrome_from_bit(i)) {
			*bad_data_bit = i;
			return;
		}
	}

	/* If data is correct, check ECC bits for errors... */
	for (i = 0; i < 8; i++) {
		if ((syndrome >> i) & 0x1) {
			*bad_ecc_bit = i;
			return;
		}
	}
}