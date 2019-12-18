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
struct semid_kernel {int /*<<< orphan*/ * label; } ;

/* Variables and functions */
 int MPC_OBJECT_SYSVSEM ; 
 int mac_labeled ; 
 int /*<<< orphan*/ * mac_sysv_sem_label_alloc () ; 

void
mac_sysvsem_init(struct semid_kernel *semakptr)
{

	if (mac_labeled & MPC_OBJECT_SYSVSEM)
		semakptr->label = mac_sysv_sem_label_alloc();
	else
		semakptr->label = NULL;
}