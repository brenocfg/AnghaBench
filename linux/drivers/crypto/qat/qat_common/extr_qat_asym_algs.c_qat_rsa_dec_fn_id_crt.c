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
 unsigned long PKE_RSA_DP2_1024 ; 
 unsigned long PKE_RSA_DP2_1536 ; 
 unsigned long PKE_RSA_DP2_2048 ; 
 unsigned long PKE_RSA_DP2_3072 ; 
 unsigned long PKE_RSA_DP2_4096 ; 
 unsigned long PKE_RSA_DP2_512 ; 

__attribute__((used)) static unsigned long qat_rsa_dec_fn_id_crt(unsigned int len)
{
	unsigned int bitslen = len << 3;

	switch (bitslen) {
	case 512:
		return PKE_RSA_DP2_512;
	case 1024:
		return PKE_RSA_DP2_1024;
	case 1536:
		return PKE_RSA_DP2_1536;
	case 2048:
		return PKE_RSA_DP2_2048;
	case 3072:
		return PKE_RSA_DP2_3072;
	case 4096:
		return PKE_RSA_DP2_4096;
	default:
		return 0;
	};
}