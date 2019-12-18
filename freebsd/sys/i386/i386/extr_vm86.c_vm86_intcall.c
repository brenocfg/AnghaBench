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
struct vm86frame {int vmf_trapno; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ setidt_disp ; 
 scalar_t__ vm86_bioscall ; 
 int /*<<< orphan*/  vm86_lock ; 

int
vm86_intcall(int intnum, struct vm86frame *vmf)
{
	int (*p)(struct vm86frame *);
	int retval;

	if (intnum < 0 || intnum > 0xff)
		return (EINVAL);

	vmf->vmf_trapno = intnum;
	p = (int (*)(struct vm86frame *))((uintptr_t)vm86_bioscall +
	    setidt_disp);
	mtx_lock(&vm86_lock);
	critical_enter();
	retval = p(vmf);
	critical_exit();
	mtx_unlock(&vm86_lock);
	return (retval);
}