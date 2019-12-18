#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned int alignment; unsigned int multiple; unsigned int minimum; unsigned int maximum; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IS_ALIGNED (unsigned long,unsigned int) ; 
 TYPE_1__ nx842_pseries_constraints ; 
 int /*<<< orphan*/  pr_debug (char*,char*,unsigned int,unsigned int) ; 
 unsigned int round_down (unsigned int,unsigned int) ; 

__attribute__((used)) static int check_constraints(unsigned long buf, unsigned int *len, bool in)
{
	if (!IS_ALIGNED(buf, nx842_pseries_constraints.alignment)) {
		pr_debug("%s buffer 0x%lx not aligned to 0x%x\n",
			 in ? "input" : "output", buf,
			 nx842_pseries_constraints.alignment);
		return -EINVAL;
	}
	if (*len % nx842_pseries_constraints.multiple) {
		pr_debug("%s buffer len 0x%x not multiple of 0x%x\n",
			 in ? "input" : "output", *len,
			 nx842_pseries_constraints.multiple);
		if (in)
			return -EINVAL;
		*len = round_down(*len, nx842_pseries_constraints.multiple);
	}
	if (*len < nx842_pseries_constraints.minimum) {
		pr_debug("%s buffer len 0x%x under minimum 0x%x\n",
			 in ? "input" : "output", *len,
			 nx842_pseries_constraints.minimum);
		return -EINVAL;
	}
	if (*len > nx842_pseries_constraints.maximum) {
		pr_debug("%s buffer len 0x%x over maximum 0x%x\n",
			 in ? "input" : "output", *len,
			 nx842_pseries_constraints.maximum);
		if (in)
			return -EINVAL;
		*len = nx842_pseries_constraints.maximum;
	}
	return 0;
}