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
typedef  int u_long ;
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int ENOTTY ; 
#define  FIOASYNC 129 
#define  FIONBIO 128 

int
shm_ioctl(struct file *fp, u_long com, void *data, struct ucred *active_cred,
    struct thread *td)
{

	switch (com) {
	case FIONBIO:
	case FIOASYNC:
		/*
		 * Allow fcntl(fd, F_SETFL, O_NONBLOCK) to work,
		 * just like it would on an unlinked regular file
		 */
		return (0);
	default:
		return (ENOTTY);
	}
}