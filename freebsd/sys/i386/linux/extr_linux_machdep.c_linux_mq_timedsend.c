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
struct linux_mq_timedsend_args {int dummy; } ;
struct kmq_timedsend_args {int dummy; } ;

/* Variables and functions */
 int ENOSYS ; 
 int sys_kmq_timedsend (struct thread*,struct kmq_timedsend_args*) ; 

int
linux_mq_timedsend(struct thread *td, struct linux_mq_timedsend_args *args)
{
#ifdef P1003_1B_MQUEUE
	return (sys_kmq_timedsend(td, (struct kmq_timedsend_args *)args));
#else
	return (ENOSYS);
#endif
}