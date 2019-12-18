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
 scalar_t__ __copy_from_user_inatomic (unsigned long*,unsigned long*,int) ; 
 int /*<<< orphan*/  access_ok (unsigned long*,int) ; 

__attribute__((used)) static inline int get_mem(unsigned long addr, unsigned long *result)
{
	unsigned long *address = (unsigned long *) addr;
	if (!access_ok(address, sizeof(unsigned long)))
		return -1;
	if (__copy_from_user_inatomic(result, address, sizeof(unsigned long)))
		return -3;
	return 0;
}