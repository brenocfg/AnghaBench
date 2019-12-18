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
struct proc {char* p_comm; } ;

/* Variables and functions */
 int EWOULDBLOCK ; 
 int hz ; 
 int kproc_shutdown_wait ; 
 int kproc_suspend (struct proc*,int) ; 
 scalar_t__ panicstr ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void
kproc_shutdown(void *arg, int howto)
{
	struct proc *p;
	int error;

	if (panicstr)
		return;

	p = (struct proc *)arg;
	printf("Waiting (max %d seconds) for system process `%s' to stop... ",
	    kproc_shutdown_wait, p->p_comm);
	error = kproc_suspend(p, kproc_shutdown_wait * hz);

	if (error == EWOULDBLOCK)
		printf("timed out\n");
	else
		printf("done\n");
}