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
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int,char*,void*,void*) ; 
 int /*<<< orphan*/  __is_lm_address (unsigned long) ; 
 int /*<<< orphan*/  __virt_to_phys_nodebug (unsigned long) ; 

phys_addr_t __virt_to_phys(unsigned long x)
{
	WARN(!__is_lm_address(x),
	     "virt_to_phys used for non-linear address: %pK (%pS)\n",
	      (void *)x,
	      (void *)x);

	return __virt_to_phys_nodebug(x);
}