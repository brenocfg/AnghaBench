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
struct l_flock {scalar_t__ l_pid; void* l_len; void* l_start; int /*<<< orphan*/  l_whence; int /*<<< orphan*/  l_type; } ;
struct flock {int l_type; scalar_t__ l_pid; scalar_t__ l_len; scalar_t__ l_start; int /*<<< orphan*/  l_whence; } ;
typedef  scalar_t__ l_pid_t ;
typedef  void* l_off_t ;

/* Variables and functions */
#define  F_RDLCK 130 
#define  F_UNLCK 129 
#define  F_WRLCK 128 
 int /*<<< orphan*/  LINUX_F_RDLCK ; 
 int /*<<< orphan*/  LINUX_F_UNLCK ; 
 int /*<<< orphan*/  LINUX_F_WRLCK ; 

__attribute__((used)) static void
bsd_to_linux_flock(struct flock *bsd_flock, struct l_flock *linux_flock)
{
	switch (bsd_flock->l_type) {
	case F_RDLCK:
		linux_flock->l_type = LINUX_F_RDLCK;
		break;
	case F_WRLCK:
		linux_flock->l_type = LINUX_F_WRLCK;
		break;
	case F_UNLCK:
		linux_flock->l_type = LINUX_F_UNLCK;
		break;
	}
	linux_flock->l_whence = bsd_flock->l_whence;
	linux_flock->l_start = (l_off_t)bsd_flock->l_start;
	linux_flock->l_len = (l_off_t)bsd_flock->l_len;
	linux_flock->l_pid = (l_pid_t)bsd_flock->l_pid;
}