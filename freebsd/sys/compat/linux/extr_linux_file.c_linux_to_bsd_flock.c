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
struct l_flock {int l_type; scalar_t__ l_pid; scalar_t__ l_len; scalar_t__ l_start; int /*<<< orphan*/  l_whence; } ;
struct flock {int l_type; scalar_t__ l_sysid; scalar_t__ l_pid; void* l_len; void* l_start; int /*<<< orphan*/  l_whence; } ;
typedef  scalar_t__ pid_t ;
typedef  void* off_t ;

/* Variables and functions */
 int F_RDLCK ; 
 int F_UNLCK ; 
 int F_WRLCK ; 
#define  LINUX_F_RDLCK 130 
#define  LINUX_F_UNLCK 129 
#define  LINUX_F_WRLCK 128 

__attribute__((used)) static void
linux_to_bsd_flock(struct l_flock *linux_flock, struct flock *bsd_flock)
{
	switch (linux_flock->l_type) {
	case LINUX_F_RDLCK:
		bsd_flock->l_type = F_RDLCK;
		break;
	case LINUX_F_WRLCK:
		bsd_flock->l_type = F_WRLCK;
		break;
	case LINUX_F_UNLCK:
		bsd_flock->l_type = F_UNLCK;
		break;
	default:
		bsd_flock->l_type = -1;
		break;
	}
	bsd_flock->l_whence = linux_flock->l_whence;
	bsd_flock->l_start = (off_t)linux_flock->l_start;
	bsd_flock->l_len = (off_t)linux_flock->l_len;
	bsd_flock->l_pid = (pid_t)linux_flock->l_pid;
	bsd_flock->l_sysid = 0;
}