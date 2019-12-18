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
struct cpumf_ctr_info {int cfvn; int csvn; } ;
typedef  enum cpumf_ctr_set { ____Placeholder_cpumf_ctr_set } cpumf_ctr_set ;

/* Variables and functions */
#define  CPUMF_CTR_SET_BASIC 133 
#define  CPUMF_CTR_SET_CRYPTO 132 
#define  CPUMF_CTR_SET_EXT 131 
#define  CPUMF_CTR_SET_MAX 130 
#define  CPUMF_CTR_SET_MT_DIAG 129 
#define  CPUMF_CTR_SET_USER 128 

__attribute__((used)) static size_t cf_diag_ctrset_size(enum cpumf_ctr_set ctrset,
				 struct cpumf_ctr_info *info)
{
	size_t ctrset_size = 0;

	switch (ctrset) {
	case CPUMF_CTR_SET_BASIC:
		if (info->cfvn >= 1)
			ctrset_size = 6;
		break;
	case CPUMF_CTR_SET_USER:
		if (info->cfvn == 1)
			ctrset_size = 6;
		else if (info->cfvn >= 3)
			ctrset_size = 2;
		break;
	case CPUMF_CTR_SET_CRYPTO:
		if (info->csvn >= 1 && info->csvn <= 5)
			ctrset_size = 16;
		else if (info->csvn == 6)
			ctrset_size = 20;
		break;
	case CPUMF_CTR_SET_EXT:
		if (info->csvn == 1)
			ctrset_size = 32;
		else if (info->csvn == 2)
			ctrset_size = 48;
		else if (info->csvn >= 3 && info->csvn <= 5)
			ctrset_size = 128;
		else if (info->csvn == 6)
			ctrset_size = 160;
		break;
	case CPUMF_CTR_SET_MT_DIAG:
		if (info->csvn > 3)
			ctrset_size = 48;
		break;
	case CPUMF_CTR_SET_MAX:
		break;
	}

	return ctrset_size;
}