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
struct flock {int /*<<< orphan*/  l_whence; int /*<<< orphan*/  l_type; int /*<<< orphan*/  l_pid; int /*<<< orphan*/  l_len; int /*<<< orphan*/  l_start; int /*<<< orphan*/  l_sysid; } ;
struct __oflock {int /*<<< orphan*/  l_whence; int /*<<< orphan*/  l_type; int /*<<< orphan*/  l_pid; int /*<<< orphan*/  l_len; int /*<<< orphan*/  l_start; int /*<<< orphan*/  l_sysid; } ;
typedef  int /*<<< orphan*/  ofl ;
typedef  int /*<<< orphan*/  fl ;

/* Variables and functions */
#define  F_GETLK 134 
#define  F_OGETLK 133 
#define  F_OSETLK 132 
#define  F_OSETLKW 131 
#define  F_SETLK 130 
#define  F_SETLKW 129 
#define  F_SETLK_REMOTE 128 
 int copyin (void*,struct flock*,int) ; 
 int copyout (struct flock*,void*,int) ; 
 int kern_fcntl (struct thread*,int,int,intptr_t) ; 

int
kern_fcntl_freebsd(struct thread *td, int fd, int cmd, long arg)
{
	struct flock fl;
	struct __oflock ofl;
	intptr_t arg1;
	int error, newcmd;

	error = 0;
	newcmd = cmd;
	switch (cmd) {
	case F_OGETLK:
	case F_OSETLK:
	case F_OSETLKW:
		/*
		 * Convert old flock structure to new.
		 */
		error = copyin((void *)(intptr_t)arg, &ofl, sizeof(ofl));
		fl.l_start = ofl.l_start;
		fl.l_len = ofl.l_len;
		fl.l_pid = ofl.l_pid;
		fl.l_type = ofl.l_type;
		fl.l_whence = ofl.l_whence;
		fl.l_sysid = 0;

		switch (cmd) {
		case F_OGETLK:
			newcmd = F_GETLK;
			break;
		case F_OSETLK:
			newcmd = F_SETLK;
			break;
		case F_OSETLKW:
			newcmd = F_SETLKW;
			break;
		}
		arg1 = (intptr_t)&fl;
		break;
	case F_GETLK:
	case F_SETLK:
	case F_SETLKW:
	case F_SETLK_REMOTE:
		error = copyin((void *)(intptr_t)arg, &fl, sizeof(fl));
		arg1 = (intptr_t)&fl;
		break;
	default:
		arg1 = arg;
		break;
	}
	if (error)
		return (error);
	error = kern_fcntl(td, fd, newcmd, arg1);
	if (error)
		return (error);
	if (cmd == F_OGETLK) {
		ofl.l_start = fl.l_start;
		ofl.l_len = fl.l_len;
		ofl.l_pid = fl.l_pid;
		ofl.l_type = fl.l_type;
		ofl.l_whence = fl.l_whence;
		error = copyout(&ofl, (void *)(intptr_t)arg, sizeof(ofl));
	} else if (cmd == F_GETLK) {
		error = copyout(&fl, (void *)(intptr_t)arg, sizeof(fl));
	}
	return (error);
}