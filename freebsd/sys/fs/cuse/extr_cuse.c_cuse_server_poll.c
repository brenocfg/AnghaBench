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
struct cdev {int dummy; } ;

/* Variables and functions */
 int POLLHUP ; 
 int POLLIN ; 
 int POLLOUT ; 
 int POLLPRI ; 
 int POLLRDNORM ; 
 int POLLWRNORM ; 

__attribute__((used)) static int
cuse_server_poll(struct cdev *dev, int events, struct thread *td)
{
	return (events & (POLLHUP | POLLPRI | POLLIN |
	    POLLRDNORM | POLLOUT | POLLWRNORM));
}