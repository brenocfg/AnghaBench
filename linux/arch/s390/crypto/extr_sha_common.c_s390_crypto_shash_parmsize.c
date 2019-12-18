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
#define  CPACF_KLMD_SHA3_224 134 
#define  CPACF_KLMD_SHA3_256 133 
#define  CPACF_KLMD_SHA3_384 132 
#define  CPACF_KLMD_SHA3_512 131 
#define  CPACF_KLMD_SHA_1 130 
#define  CPACF_KLMD_SHA_256 129 
#define  CPACF_KLMD_SHA_512 128 
 int EINVAL ; 

__attribute__((used)) static int s390_crypto_shash_parmsize(int func)
{
	switch (func) {
	case CPACF_KLMD_SHA_1:
		return 20;
	case CPACF_KLMD_SHA_256:
		return 32;
	case CPACF_KLMD_SHA_512:
		return 64;
	case CPACF_KLMD_SHA3_224:
	case CPACF_KLMD_SHA3_256:
	case CPACF_KLMD_SHA3_384:
	case CPACF_KLMD_SHA3_512:
		return 200;
	default:
		return -EINVAL;
	}
}