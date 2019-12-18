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
struct proc {int /*<<< orphan*/ * p_label; } ;

/* Variables and functions */
 int MPC_OBJECT_PROC ; 
 int mac_labeled ; 
 int /*<<< orphan*/ * mac_proc_label_alloc () ; 

void
mac_proc_init(struct proc *p)
{

	if (mac_labeled & MPC_OBJECT_PROC)
		p->p_label = mac_proc_label_alloc();
	else
		p->p_label = NULL;
}