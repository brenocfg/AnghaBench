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
 unsigned long __mk_vsid_data (int /*<<< orphan*/ ,int,unsigned long) ; 
 int /*<<< orphan*/  get_kernel_vsid (unsigned long,int) ; 

__attribute__((used)) static inline unsigned long mk_vsid_data(unsigned long ea, int ssize,
					 unsigned long flags)
{
	return __mk_vsid_data(get_kernel_vsid(ea, ssize), ssize, flags);
}