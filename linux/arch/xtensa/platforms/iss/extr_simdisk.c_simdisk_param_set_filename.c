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
struct kernel_param {int dummy; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (char const**) ; 
 int EINVAL ; 
 char const** filename ; 
 scalar_t__ n_files ; 

__attribute__((used)) static int simdisk_param_set_filename(const char *val,
		const struct kernel_param *kp)
{
	if (n_files < ARRAY_SIZE(filename))
		filename[n_files++] = val;
	else
		return -EINVAL;
	return 0;
}