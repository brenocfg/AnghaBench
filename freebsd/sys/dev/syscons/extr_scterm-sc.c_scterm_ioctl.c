#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  back; int /*<<< orphan*/  fore; } ;
struct TYPE_9__ {int /*<<< orphan*/  back; int /*<<< orphan*/  fore; } ;
struct TYPE_13__ {int size; TYPE_3__ mv_rev; TYPE_1__ mv_norm; } ;
typedef  TYPE_5__ vid_info_t ;
typedef  int u_long ;
struct TYPE_12__ {int /*<<< orphan*/  bg; int /*<<< orphan*/  fg; } ;
struct TYPE_10__ {int /*<<< orphan*/  bg; int /*<<< orphan*/  fg; } ;
struct TYPE_14__ {int cur_attr; TYPE_4__ rev_color; TYPE_2__ std_color; } ;
typedef  TYPE_6__ term_stat ;
struct vid_info {int dummy; } ;
struct tty {int dummy; } ;
struct thread {int dummy; } ;
struct TYPE_15__ {TYPE_6__* ts; } ;
typedef  TYPE_7__ scr_stat ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
#define  CONS_GETINFO 129 
 int EINVAL ; 
 int ENOIOCTL ; 
#define  GIO_ATTR 128 

__attribute__((used)) static int
scterm_ioctl(scr_stat *scp, struct tty *tp, u_long cmd, caddr_t data,
	     struct thread *td)
{
	term_stat *tcp = scp->ts;
	vid_info_t *vi;

	switch (cmd) {
	case GIO_ATTR:      	/* get current attributes */
		/* FIXME: */
		*(int*)data = (tcp->cur_attr >> 8) & 0xff;
		return 0;
	case CONS_GETINFO:  	/* get current (virtual) console info */
		vi = (vid_info_t *)data;
		if (vi->size != sizeof(struct vid_info))
			return EINVAL;
		vi->mv_norm.fore = tcp->std_color.fg;
		vi->mv_norm.back = tcp->std_color.bg;
		vi->mv_rev.fore = tcp->rev_color.fg;
		vi->mv_rev.back = tcp->rev_color.bg;
		/*
		 * The other fields are filled by the upper routine. XXX
		 */
		return ENOIOCTL;
	}
	return ENOIOCTL;
}