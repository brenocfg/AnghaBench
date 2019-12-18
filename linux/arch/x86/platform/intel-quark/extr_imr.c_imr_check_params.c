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
typedef  size_t phys_addr_t ;

/* Variables and functions */
 int EINVAL ; 
 size_t IMR_MASK ; 
 int /*<<< orphan*/  pr_err (char*,size_t*,size_t) ; 

__attribute__((used)) static int imr_check_params(phys_addr_t base, size_t size)
{
	if ((base & IMR_MASK) || (size & IMR_MASK)) {
		pr_err("base %pa size 0x%08zx must align to 1KiB\n",
			&base, size);
		return -EINVAL;
	}
	if (size == 0)
		return -EINVAL;

	return 0;
}