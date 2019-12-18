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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct futex_st0 {int oparg; int* oldval; } ;

/* Variables and functions */
 int EFAULT ; 
 scalar_t__ cp_slow0 (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,struct futex_st0*) ; 
 int /*<<< orphan*/  futex_xorl_slow0 ; 

int
futex_xorl(int oparg, uint32_t *uaddr, int *oldval)
{
	struct futex_st0 st;

	st.oparg = oparg;
	st.oldval = oldval;
	if (cp_slow0((vm_offset_t)uaddr, sizeof(uint32_t), true,
	    futex_xorl_slow0, &st) != 0)
		return (-EFAULT);
	return (0);
}