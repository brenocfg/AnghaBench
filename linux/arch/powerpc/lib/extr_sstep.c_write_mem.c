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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  address_ok (struct pt_regs*,unsigned long,int) ; 
 int write_mem_aligned (unsigned long,unsigned long,int,struct pt_regs*) ; 
 int write_mem_unaligned (unsigned long,unsigned long,int,struct pt_regs*) ; 

__attribute__((used)) static int write_mem(unsigned long val, unsigned long ea, int nb,
			       struct pt_regs *regs)
{
	if (!address_ok(regs, ea, nb))
		return -EFAULT;
	if ((ea & (nb - 1)) == 0)
		return write_mem_aligned(val, ea, nb, regs);
	return write_mem_unaligned(val, ea, nb, regs);
}