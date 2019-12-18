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
struct thread {char* td_name; } ;

/* Variables and functions */
 int EWOULDBLOCK ; 
 int hz ; 
 int kproc_shutdown_wait ; 
 int kthread_suspend (struct thread*,int) ; 
 scalar_t__ panicstr ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void
kthread_shutdown(void *arg, int howto)
{
	struct thread *td;
	int error;

	if (panicstr)
		return;

	td = (struct thread *)arg;
	printf("Waiting (max %d seconds) for system thread `%s' to stop... ",
	    kproc_shutdown_wait, td->td_name);
	error = kthread_suspend(td, kproc_shutdown_wait * hz);

	if (error == EWOULDBLOCK)
		printf("timed out\n");
	else
		printf("done\n");
}