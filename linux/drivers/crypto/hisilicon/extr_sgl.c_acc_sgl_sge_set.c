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
typedef  scalar_t__ u32 ;
struct kernel_param {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ HISI_ACC_SGL_SGE_NR_MAX ; 
 int kstrtou32 (char const*,int,scalar_t__*) ; 
 int param_set_int (char const*,struct kernel_param const*) ; 

__attribute__((used)) static int acc_sgl_sge_set(const char *val, const struct kernel_param *kp)
{
	int ret;
	u32 n;

	if (!val)
		return -EINVAL;

	ret = kstrtou32(val, 10, &n);
	if (ret != 0 || n > HISI_ACC_SGL_SGE_NR_MAX || n == 0)
		return -EINVAL;

	return param_set_int(val, kp);
}