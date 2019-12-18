#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  sg_flags; int /*<<< orphan*/  c_lflag; int /*<<< orphan*/  c_cflag; int /*<<< orphan*/  c_oflag; int /*<<< orphan*/  c_iflag; } ;
struct TYPE_8__ {int /*<<< orphan*/  d_lb; TYPE_1__ d_t; } ;
struct TYPE_7__ {int /*<<< orphan*/  t_setmask; int /*<<< orphan*/  t_clrmask; } ;

/* Variables and functions */
 size_t M_CONTROL ; 
 size_t M_INPUT ; 
 size_t M_LINED ; 
 size_t M_LOCAL ; 
 size_t M_OUTPUT ; 
 scalar_t__ MacroLvl ; 
 size_t QU_IO ; 
 int /*<<< orphan*/  SHTTY ; 
 int Tty_quote_mode ; 
 TYPE_3__ edtty ; 
 int /*<<< orphan*/  errno ; 
 TYPE_3__ qutty ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int tty_setty (int /*<<< orphan*/ ,TYPE_3__*) ; 
 TYPE_2__** ttylist ; 
 int /*<<< orphan*/  xprintf (char*,int /*<<< orphan*/ ) ; 

void
QuoteModeOn(void)
{
    if (MacroLvl >= 0)
	return;

#ifndef WINNT_NATIVE
    qutty = edtty;

#if defined(TERMIO) || defined(POSIX)
    qutty.d_t.c_iflag &= ~ttylist[QU_IO][M_INPUT].t_clrmask;
    qutty.d_t.c_iflag |=  ttylist[QU_IO][M_INPUT].t_setmask;

    qutty.d_t.c_oflag &= ~ttylist[QU_IO][M_OUTPUT].t_clrmask;
    qutty.d_t.c_oflag |=  ttylist[QU_IO][M_OUTPUT].t_setmask;

    qutty.d_t.c_cflag &= ~ttylist[QU_IO][M_CONTROL].t_clrmask;
    qutty.d_t.c_cflag |=  ttylist[QU_IO][M_CONTROL].t_setmask;

    qutty.d_t.c_lflag &= ~ttylist[QU_IO][M_LINED].t_clrmask;
    qutty.d_t.c_lflag |=  ttylist[QU_IO][M_LINED].t_setmask;
#else /* GSTTY */
    qutty.d_t.sg_flags &= ~ttylist[QU_IO][M_CONTROL].t_clrmask;
    qutty.d_t.sg_flags |= ttylist[QU_IO][M_CONTROL].t_setmask;
    qutty.d_lb &= ~ttylist[QU_IO][M_LOCAL].t_clrmask;
    qutty.d_lb |= ttylist[QU_IO][M_LOCAL].t_setmask;

#endif /* TERMIO || POSIX */
    if (tty_setty(SHTTY, &qutty) == -1) {
#ifdef DEBUG_TTY
	xprintf("QuoteModeOn: tty_setty: %s\n", strerror(errno));
#endif /* DEBUG_TTY */
	return;
    }
#endif /* !WINNT_NATIVE */
    Tty_quote_mode = 1;
    return;
}