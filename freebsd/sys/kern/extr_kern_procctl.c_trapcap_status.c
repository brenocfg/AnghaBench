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
 int P2_TRAPCAP ; 
 int PROC_TRAPCAP_CTL_DISABLE ; 
 int PROC_TRAPCAP_CTL_ENABLE ; 

__attribute__((used)) static int
trapcap_status(struct thread *td, struct proc *p, int *data)
{

	*data = (p->p_flag2 & P2_TRAPCAP) != 0 ? PROC_TRAPCAP_CTL_ENABLE :
	    PROC_TRAPCAP_CTL_DISABLE;
	return (0);
}