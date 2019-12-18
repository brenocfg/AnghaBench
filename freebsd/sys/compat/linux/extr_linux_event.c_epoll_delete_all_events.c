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
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVFILT_READ ; 
 int /*<<< orphan*/  EVFILT_WRITE ; 
 int epoll_delete_event (struct thread*,struct file*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
epoll_delete_all_events(struct thread *td, struct file *epfp, int fd)
{
	int error1, error2;

	error1 = epoll_delete_event(td, epfp, fd, EVFILT_READ);
	error2 = epoll_delete_event(td, epfp, fd, EVFILT_WRITE);

	/* return 0 if at least one result positive */
	return (error1 == 0 ? 0 : error2);
}