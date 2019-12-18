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
struct thread {int dummy; } ;
struct proc {int p_flag2; } ;

/* Variables and functions */
#define  P2_PROTMAX_DISABLE 129 
#define  P2_PROTMAX_ENABLE 128 
 int PROC_ASLR_NOFORCE ; 
 int PROC_PROTMAX_ACTIVE ; 
 int PROC_PROTMAX_FORCE_DISABLE ; 
 int PROC_PROTMAX_FORCE_ENABLE ; 
 scalar_t__ PROT_READ ; 
 scalar_t__ kern_mmap_maxprot (struct proc*,scalar_t__) ; 

__attribute__((used)) static int
protmax_status(struct thread *td, struct proc *p, int *data)
{
	int d;

	switch (p->p_flag2 & (P2_PROTMAX_ENABLE | P2_PROTMAX_DISABLE)) {
	case 0:
		d = PROC_ASLR_NOFORCE;
		break;
	case P2_PROTMAX_ENABLE:
		d = PROC_PROTMAX_FORCE_ENABLE;
		break;
	case P2_PROTMAX_DISABLE:
		d = PROC_PROTMAX_FORCE_DISABLE;
		break;
	}
	if (kern_mmap_maxprot(p, PROT_READ) == PROT_READ)
		d |= PROC_PROTMAX_ACTIVE;
	*data = d;
	return (0);
}