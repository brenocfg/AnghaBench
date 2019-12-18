#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ len; int /*<<< orphan*/ * buf; } ;
struct TYPE_6__ {int c_iflag; int c_oflag; int c_cflag; int c_lflag; int sg_flags; int /*<<< orphan*/  c_line; } ;
struct TYPE_8__ {int d_lb; TYPE_1__ d_t; } ;
struct TYPE_7__ {int t_clrmask; int t_setmask; } ;

/* Variables and functions */
 int /*<<< orphan*/  CheckMaps () ; 
 size_t ED_IO ; 
 int /*<<< orphan*/  GetTermCaps () ; 
 scalar_t__ GettingInput ; 
 int /*<<< orphan*/  GotTermCaps ; 
 scalar_t__ KillPos ; 
 TYPE_5__* KillRing ; 
 scalar_t__ KillRingLen ; 
 int KillRingMax ; 
 size_t M_CONTROL ; 
 size_t M_INPUT ; 
 size_t M_LINED ; 
 size_t M_LOCAL ; 
 size_t M_OUTPUT ; 
 int /*<<< orphan*/  NTTYDISC ; 
 int /*<<< orphan*/  ResetInLine (int) ; 
 scalar_t__ T_Tabs ; 
 int XTABS ; 
 scalar_t__ YankPos ; 
 int ed_Setup (int /*<<< orphan*/ ) ; 
 TYPE_3__ edtty ; 
 int /*<<< orphan*/  tty_setchar (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ttychars ; 
 TYPE_2__** ttylist ; 
 int /*<<< orphan*/  xfree (int /*<<< orphan*/ *) ; 

void
ed_Init(void)
{
    ResetInLine(1);		/* reset the input pointers */
    GettingInput = 0;		/* just in case */
#ifdef notdef
    /* XXX This code was here before the kill ring:
    LastKill = KillBuf;		/ * no kill buffer * /
       If there was any reason for that other than to make sure LastKill
       was initialized, the code below should go in here instead - but
       it doesn't seem reasonable to lose the entire kill ring (which is
       "self-initializing") just because you set $term or whatever, so
       presumably this whole '#ifdef notdef' should just be taken out.  */

    {				/* no kill ring - why? */
	int i;
	for (i = 0; i < KillRingMax; i++) {
	    xfree(KillRing[i].buf);
	    KillRing[i].buf = NULL;
	    KillRing[i].len = 0;
	}
	YankPos = KillPos = 0;
	KillRingLen = 0;
    }
#endif

#ifdef DEBUG_EDIT
    CheckMaps();		/* do a little error checking on key maps */
#endif 

    if (ed_Setup(0) == -1)
	return;

    /*
     * if we have been called before but GotTermCaps isn't set, our TERM has
     * changed, so get new termcaps and try again
     */

    if (!GotTermCaps)
	GetTermCaps();		/* does the obvious, but gets term type each
				 * time */

#ifndef WINNT_NATIVE
# if defined(TERMIO) || defined(POSIX)
    edtty.d_t.c_iflag &= ~ttylist[ED_IO][M_INPUT].t_clrmask;
    edtty.d_t.c_iflag |=  ttylist[ED_IO][M_INPUT].t_setmask;

    edtty.d_t.c_oflag &= ~ttylist[ED_IO][M_OUTPUT].t_clrmask;
    edtty.d_t.c_oflag |=  ttylist[ED_IO][M_OUTPUT].t_setmask;

    edtty.d_t.c_cflag &= ~ttylist[ED_IO][M_CONTROL].t_clrmask;
    edtty.d_t.c_cflag |=  ttylist[ED_IO][M_CONTROL].t_setmask;

    edtty.d_t.c_lflag &= ~ttylist[ED_IO][M_LINED].t_clrmask;
    edtty.d_t.c_lflag |=  ttylist[ED_IO][M_LINED].t_setmask;


#  if defined(IRIX3_3) && SYSVREL < 4
    edtty.d_t.c_line = NTTYDISC;
#  endif /* IRIX3_3 && SYSVREL < 4 */

# else /* GSTTY */

    if (T_Tabs) {	/* order of &= and |= is important to XTABS */
	edtty.d_t.sg_flags &= ~(ttylist[ED_IO][M_CONTROL].t_clrmask | XTABS);
	edtty.d_t.sg_flags |=   ttylist[ED_IO][M_CONTROL].t_setmask;
    }
    else {
	edtty.d_t.sg_flags &= ~ttylist[ED_IO][M_CONTROL].t_clrmask;
	edtty.d_t.sg_flags |= (ttylist[ED_IO][M_CONTROL].t_setmask | XTABS);
    }

    edtty.d_lb &= ~ttylist[ED_IO][M_LOCAL].t_clrmask;
    edtty.d_lb |=  ttylist[ED_IO][M_LOCAL].t_setmask;
# endif /* POSIX || TERMIO */

    tty_setchar(&edtty, ttychars[ED_IO]);
#endif /* WINNT_NATIVE */
}