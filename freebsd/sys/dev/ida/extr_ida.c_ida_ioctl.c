#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
struct thread {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  buf; } ;
struct ida_user_command {int /*<<< orphan*/  blkno; int /*<<< orphan*/  drive; int /*<<< orphan*/  command; TYPE_1__ d; } ;
struct ida_softc {int /*<<< orphan*/  lock; } ;
struct cmd_info {int len; int flags; } ;
struct cdev {scalar_t__ si_drv1; } ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  data ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOIOCTL ; 
#define  IDAIO_COMMAND 128 
 struct cmd_info* ida_cmd_lookup (int /*<<< orphan*/ ) ; 
 int ida_command (struct ida_softc*,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ida_ioctl (struct cdev *dev, u_long cmd, caddr_t addr, int32_t flag, struct thread *td)
{
	struct ida_softc *sc;
	struct ida_user_command *uc;
	struct cmd_info *ci;
	int len;
	int flags;
	int error;
	int data;
	void *daddr;

	sc = (struct ida_softc *)dev->si_drv1;
	uc = (struct ida_user_command *)addr;
	error = 0;

	switch (cmd) {
	case IDAIO_COMMAND:
		ci = ida_cmd_lookup(uc->command);
		if (ci == NULL) {
			error = EINVAL;
			break;
		}
		len = ci->len;
		flags = ci->flags;
		if (len)
			daddr = &uc->d.buf;
		else {
			daddr = &data;
			len = sizeof(data);
		}
		mtx_lock(&sc->lock);
		error = ida_command(sc, uc->command, daddr, len,
				    uc->drive, uc->blkno, flags);
		mtx_unlock(&sc->lock);
		break;
	default:
		error = ENOIOCTL;
		break;
	}
	return (error);
}