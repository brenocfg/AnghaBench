#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int fore; int back; } ;
struct TYPE_8__ {int fore; int back; } ;
struct TYPE_11__ {int size; TYPE_2__ mv_rev; TYPE_1__ mv_norm; int /*<<< orphan*/  mv_csz; int /*<<< orphan*/  mv_rsz; int /*<<< orphan*/  mv_col; int /*<<< orphan*/  mv_row; } ;
typedef  TYPE_4__ vid_info_t ;
typedef  int /*<<< orphan*/  u_long ;
struct TYPE_12__ {int /*<<< orphan*/  tp_col; int /*<<< orphan*/  tp_row; } ;
typedef  TYPE_5__ teken_pos_t ;
struct tty {int dummy; } ;
struct thread {int dummy; } ;
struct terminal {TYPE_3__* tm_class; int /*<<< orphan*/  tm_emulator; } ;
typedef  scalar_t__ caddr_t ;
struct TYPE_10__ {int (* tc_ioctl ) (struct terminal*,int /*<<< orphan*/ ,scalar_t__,struct thread*) ;} ;

/* Variables and functions */
#define  CONS_GETINFO 128 
 int EINVAL ; 
 int stub1 (struct terminal*,int /*<<< orphan*/ ,scalar_t__,struct thread*) ; 
 TYPE_5__* teken_get_cursor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  teken_get_defattr_cons25 (int /*<<< orphan*/ *,int*,int*) ; 
 TYPE_5__* teken_get_winsize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_lock (struct tty*) ; 
 struct terminal* tty_softc (struct tty*) ; 
 int /*<<< orphan*/  tty_unlock (struct tty*) ; 

__attribute__((used)) static int
termtty_ioctl(struct tty *tp, u_long cmd, caddr_t data, struct thread *td)
{
	struct terminal *tm = tty_softc(tp);
	int error;

	switch (cmd) {
	case CONS_GETINFO: {
		vid_info_t *vi = (vid_info_t *)data;
		const teken_pos_t *p;
		int fg, bg;

		if (vi->size != sizeof(vid_info_t))
			return (EINVAL);

		/* Already help the console driver by filling in some data. */
		p = teken_get_cursor(&tm->tm_emulator);
		vi->mv_row = p->tp_row;
		vi->mv_col = p->tp_col;

		p = teken_get_winsize(&tm->tm_emulator);
		vi->mv_rsz = p->tp_row;
		vi->mv_csz = p->tp_col;

		teken_get_defattr_cons25(&tm->tm_emulator, &fg, &bg);
		vi->mv_norm.fore = fg;
		vi->mv_norm.back = bg;
		/* XXX: keep vidcontrol happy; bold backgrounds. */
		vi->mv_rev.fore = bg;
		vi->mv_rev.back = fg & 0x7;
		break;
	}
	}

	/*
	 * Unlike various other drivers, this driver will never
	 * deallocate TTYs.  This means it's safe to temporarily unlock
	 * the TTY when handling ioctls.
	 */
	tty_unlock(tp);
	error = tm->tm_class->tc_ioctl(tm, cmd, data, td);
	tty_lock(tp);
	return (error);
}