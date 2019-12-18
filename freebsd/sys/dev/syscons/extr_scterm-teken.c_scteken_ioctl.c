#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int fore; int back; } ;
struct TYPE_7__ {int fore; int back; } ;
struct TYPE_9__ {int size; TYPE_2__ mv_norm; TYPE_1__ mv_rev; } ;
typedef  TYPE_3__ vid_info_t ;
typedef  int u_long ;
struct TYPE_10__ {int /*<<< orphan*/  ts_teken; } ;
typedef  TYPE_4__ teken_stat ;
struct vid_info {int dummy; } ;
struct tty {int dummy; } ;
struct thread {int dummy; } ;
struct TYPE_11__ {TYPE_4__* ts; } ;
typedef  TYPE_5__ scr_stat ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
#define  CONS_GETINFO 129 
 int EINVAL ; 
 int ENOIOCTL ; 
#define  GIO_ATTR 128 
 int scteken_te_to_sc_attr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  teken_get_curattr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  teken_get_defattr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
scteken_ioctl(scr_stat *scp, struct tty *tp, u_long cmd, caddr_t data,
	     struct thread *td)
{
	teken_stat *ts = scp->ts;
	vid_info_t *vi;
	int attr;

	switch (cmd) {
	case GIO_ATTR:      	/* get current attributes */
		*(int*)data =
		    scteken_te_to_sc_attr(teken_get_curattr(&ts->ts_teken));
		return (0);
	case CONS_GETINFO:  	/* get current (virtual) console info */
		vi = (vid_info_t *)data;
		if (vi->size != sizeof(struct vid_info))
			return EINVAL;

		attr = scteken_te_to_sc_attr(teken_get_defattr(&ts->ts_teken));
		vi->mv_norm.fore = attr & 0x0f;
		vi->mv_norm.back = (attr >> 4) & 0x0f;
		vi->mv_rev.fore = vi->mv_norm.back;
		vi->mv_rev.back = vi->mv_norm.fore;
		/*
		 * The other fields are filled by the upper routine. XXX
		 */
		return (ENOIOCTL);
	}

	return (ENOIOCTL);
}