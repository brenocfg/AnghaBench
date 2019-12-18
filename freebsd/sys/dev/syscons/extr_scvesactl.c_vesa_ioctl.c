#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
struct tty {int dummy; } ;
struct thread {int dummy; } ;
struct TYPE_9__ {TYPE_2__* sc; } ;
typedef  TYPE_3__ scr_stat ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_8__ {TYPE_1__* adp; } ;
struct TYPE_7__ {int va_flags; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOIOCTL ; 
 char IOCGROUP (int) ; 
 int IOC_DIRMASK ; 
 int IOC_VOID ; 
 int M_VESA_BASE ; 
 int M_VESA_FULL_1280 ; 
 int M_VESA_MODE_MAX ; 
 TYPE_3__* SC_STAT (struct tty*) ; 
#define  SW_TEXT_132x25 160 
#define  SW_TEXT_132x30 159 
#define  SW_TEXT_132x43 158 
#define  SW_TEXT_132x50 157 
#define  SW_TEXT_132x60 156 
#define  SW_VESA_1024x768 155 
#define  SW_VESA_1280x1024 154 
#define  SW_VESA_32K_1024 153 
#define  SW_VESA_32K_1280 152 
#define  SW_VESA_32K_320 151 
#define  SW_VESA_32K_640 150 
#define  SW_VESA_32K_800 149 
#define  SW_VESA_64K_1024 148 
#define  SW_VESA_64K_1280 147 
#define  SW_VESA_64K_320 146 
#define  SW_VESA_64K_640 145 
#define  SW_VESA_64K_800 144 
#define  SW_VESA_800x600 143 
#define  SW_VESA_C132x25 142 
#define  SW_VESA_C132x43 141 
#define  SW_VESA_C132x50 140 
#define  SW_VESA_C132x60 139 
#define  SW_VESA_C80x60 138 
#define  SW_VESA_CG1024x768 137 
#define  SW_VESA_CG1280x1024 136 
#define  SW_VESA_CG640x400 135 
#define  SW_VESA_CG640x480 134 
#define  SW_VESA_CG800x600 133 
#define  SW_VESA_FULL_1024 132 
#define  SW_VESA_FULL_1280 131 
#define  SW_VESA_FULL_320 130 
#define  SW_VESA_FULL_640 129 
#define  SW_VESA_FULL_800 128 
 int V_ADP_MODECHANGE ; 
 int prev_user_ioctl (struct tty*,int,int /*<<< orphan*/ ,struct thread*) ; 
 int sc_set_graphics_mode (TYPE_3__*,struct tty*,int) ; 
 int sc_set_text_mode (TYPE_3__*,struct tty*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct tty*,int,int /*<<< orphan*/ ,struct thread*) ; 

__attribute__((used)) static int
vesa_ioctl(struct tty *tp, u_long cmd, caddr_t data, struct thread *td)
{
	scr_stat *scp;
	int mode;

	scp = SC_STAT(tp);

	switch (cmd) {

	/* generic text modes */
	case SW_TEXT_132x25: case SW_TEXT_132x30:
	case SW_TEXT_132x43: case SW_TEXT_132x50:
	case SW_TEXT_132x60:
		if (!(scp->sc->adp->va_flags & V_ADP_MODECHANGE))
			return ENODEV;
		return sc_set_text_mode(scp, tp, cmd & 0xff, 0, 0, 0, 0);

	/* text modes */
	case SW_VESA_C80x60:
	case SW_VESA_C132x25:
	case SW_VESA_C132x43:
	case SW_VESA_C132x50:
	case SW_VESA_C132x60:
		if (!(scp->sc->adp->va_flags & V_ADP_MODECHANGE))
			return ENODEV;
		mode = (cmd & 0xff) + M_VESA_BASE;
		return sc_set_text_mode(scp, tp, mode, 0, 0, 0, 0);

	/* graphics modes */
	case SW_VESA_32K_320: 	case SW_VESA_64K_320: 
	case SW_VESA_FULL_320:

	case SW_VESA_CG640x400:

	case SW_VESA_CG640x480:
	case SW_VESA_32K_640:	case SW_VESA_64K_640:
	case SW_VESA_FULL_640:

	case SW_VESA_800x600:	case SW_VESA_CG800x600:
	case SW_VESA_32K_800:	case SW_VESA_64K_800:
	case SW_VESA_FULL_800:

	case SW_VESA_1024x768:	case SW_VESA_CG1024x768:
	case SW_VESA_32K_1024:	case SW_VESA_64K_1024:
	case SW_VESA_FULL_1024:

	case SW_VESA_1280x1024:	case SW_VESA_CG1280x1024:
	case SW_VESA_32K_1280:	case SW_VESA_64K_1280:
	case SW_VESA_FULL_1280:
		if (!(scp->sc->adp->va_flags & V_ADP_MODECHANGE))
			return ENODEV;
		mode = (cmd & 0xff) + M_VESA_BASE;
		return sc_set_graphics_mode(scp, tp, mode);
	default:
		if (IOCGROUP(cmd) == 'V') {
			if (!(scp->sc->adp->va_flags & V_ADP_MODECHANGE))
				return ENODEV;

			mode = (cmd & 0xff) + M_VESA_BASE;

			if (((cmd & IOC_DIRMASK) == IOC_VOID) &&
			    (mode > M_VESA_FULL_1280) &&
			    (mode < M_VESA_MODE_MAX))
				return sc_set_graphics_mode(scp, tp, mode);
		}
	}

	if (prev_user_ioctl)
		return (*prev_user_ioctl)(tp, cmd, data, td);
	else
		return ENOIOCTL;
}