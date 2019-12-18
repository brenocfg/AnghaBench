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
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLIN ; 
 int EPOLLOUT ; 
 int EPOLLRDNORM ; 
 int EPOLLWRNORM ; 
 int HZ ; 
 int /*<<< orphan*/  TRACE_TEXT (char*) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 scalar_t__ dtlk_has_indexing ; 
 int /*<<< orphan*/  dtlk_process_list ; 
 scalar_t__ dtlk_readable () ; 
 int /*<<< orphan*/  dtlk_timer ; 
 scalar_t__ dtlk_writeable () ; 
 int jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t dtlk_poll(struct file *file, poll_table * wait)
{
	__poll_t mask = 0;
	unsigned long expires;

	TRACE_TEXT(" dtlk_poll");
	/*
	   static long int j;
	   printk(".");
	   printk("<%ld>", jiffies-j);
	   j=jiffies;
	 */
	poll_wait(file, &dtlk_process_list, wait);

	if (dtlk_has_indexing && dtlk_readable()) {
	        del_timer(&dtlk_timer);
		mask = EPOLLIN | EPOLLRDNORM;
	}
	if (dtlk_writeable()) {
	        del_timer(&dtlk_timer);
		mask |= EPOLLOUT | EPOLLWRNORM;
	}
	/* there are no exception conditions */

	/* There won't be any interrupts, so we set a timer instead. */
	expires = jiffies + 3*HZ / 100;
	mod_timer(&dtlk_timer, expires);

	return mask;
}