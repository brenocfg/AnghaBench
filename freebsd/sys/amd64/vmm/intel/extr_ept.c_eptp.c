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
typedef  int uint64_t ;

/* Variables and functions */
 int EPT_ENABLE_AD_BITS ; 
 int EPT_PWLEVELS ; 
 int PAT_WRITE_BACK ; 
 scalar_t__ ept_enable_ad_bits ; 

uint64_t
eptp(uint64_t pml4)
{
	uint64_t eptp_val;

	eptp_val = pml4 | (EPT_PWLEVELS - 1) << 3 | PAT_WRITE_BACK;
	if (ept_enable_ad_bits)
		eptp_val |= EPT_ENABLE_AD_BITS;

	return (eptp_val);
}