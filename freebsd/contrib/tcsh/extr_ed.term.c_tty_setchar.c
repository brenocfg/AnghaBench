#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct termios {unsigned char* c_cc; unsigned char sg_erase; unsigned char sg_kill; } ;
struct tchars {unsigned char t_intrc; unsigned char t_quitc; unsigned char t_startc; unsigned char t_stopc; unsigned char t_eofc; unsigned char t_brkc; } ;
struct ttypagestat {unsigned char tps_statc; unsigned char tps_pagec; unsigned char tps_pgoffc; scalar_t__ tps_flag; scalar_t__ tps_lpos; scalar_t__ tps_length; } ;
struct ltchars {unsigned char t_suspc; unsigned char t_dsuspc; unsigned char t_rprntc; unsigned char t_flushc; unsigned char t_werasc; unsigned char t_lnextc; } ;
struct TYPE_3__ {struct termios d_t; struct tchars d_tc; struct ttypagestat d_pc; struct ltchars d_ltc; } ;
typedef  TYPE_1__ ttydata_t ;
struct termio {unsigned char* c_cc; unsigned char sg_erase; unsigned char sg_kill; } ;
struct sgttyb {unsigned char* c_cc; unsigned char sg_erase; unsigned char sg_kill; } ;

/* Variables and functions */
 size_t C_BRK ; 
 size_t C_DISCARD ; 
 size_t C_DSUSP ; 
 size_t C_DSWTCH ; 
 size_t C_EOF ; 
 size_t C_EOL ; 
 size_t C_EOL2 ; 
 size_t C_ERASE ; 
 size_t C_ERASE2 ; 
 size_t C_INTR ; 
 size_t C_KILL ; 
 size_t C_KILL2 ; 
 size_t C_LNEXT ; 
 size_t C_MIN ; 
 size_t C_PAGE ; 
 size_t C_PGOFF ; 
 size_t C_QUIT ; 
 size_t C_REPRINT ; 
 size_t C_START ; 
 size_t C_STATUS ; 
 size_t C_STOP ; 
 size_t C_SUSP ; 
 size_t C_SWTCH ; 
 size_t C_TIME ; 
 size_t C_WERASE ; 
 size_t VDISCARD ; 
 size_t VDSUSP ; 
 size_t VDSWTCH ; 
 size_t VEOF ; 
 size_t VEOL ; 
 size_t VEOL2 ; 
 size_t VERASE ; 
 size_t VERASE2 ; 
 size_t VINTR ; 
 size_t VKILL ; 
 size_t VKILL2 ; 
 size_t VLNEXT ; 
 size_t VMIN ; 
 size_t VPAGE ; 
 size_t VPGOFF ; 
 size_t VQUIT ; 
 size_t VREPRINT ; 
 size_t VSTART ; 
 size_t VSTATUS ; 
 size_t VSTOP ; 
 size_t VSUSP ; 
 size_t VSWTCH ; 
 size_t VTIME ; 
 size_t VWERASE ; 

void
tty_setchar(ttydata_t *td, unsigned char *s)
{   
#ifdef TIOCGLTC
    {
	struct ltchars *n = &td->d_ltc; 

	n->t_suspc 		= s[C_SUSP];
	n->t_dsuspc		= s[C_DSUSP];
	n->t_rprntc		= s[C_REPRINT];
	n->t_flushc		= s[C_DISCARD];
	n->t_werasc		= s[C_WERASE];
	n->t_lnextc		= s[C_LNEXT];
    }
#endif /* TIOCGLTC */

#if defined(POSIX) || defined(TERMIO)
    {
# ifdef POSIX
	struct termios *n = &td->d_t;
# else
	struct termio *n = &td->d_t;
# endif /* POSIX */

# ifdef VINTR
	n->c_cc[VINTR]		= s[C_INTR];
# endif /* VINTR */
# ifdef VQUIT
	n->c_cc[VQUIT]		= s[C_QUIT];
# endif /* VQUIT */
# ifdef VERASE
	n->c_cc[VERASE]		= s[C_ERASE];
# endif /* VERASE */
# ifdef VKILL
	n->c_cc[VKILL]		= s[C_KILL];
# endif /* VKILL */
# ifdef VEOF
	n->c_cc[VEOF]		= s[C_EOF];
# endif /* VEOF */
# ifdef VEOL
	n->c_cc[VEOL]		= s[C_EOL];
# endif /* VEOL */
# ifdef VEOL2
	n->c_cc[VEOL2]		= s[C_EOL2];
# endif  /* VEOL2 */
# ifdef VSWTCH
	n->c_cc[VSWTCH]		= s[C_SWTCH];
# endif /* VSWTCH */
# ifdef VDSWTCH
	n->c_cc[VDSWTCH]	= s[C_DSWTCH];
# endif /* VDSWTCH */
# ifdef VERASE2
	n->c_cc[VERASE2]	= s[C_ERASE2];
# endif /* VERASE2 */
# ifdef VSTART
	n->c_cc[VSTART]		= s[C_START];
# endif /* VSTART */
# ifdef VSTOP
	n->c_cc[VSTOP]		= s[C_STOP];
# endif /* VSTOP */
# ifdef VWERASE
	n->c_cc[VWERASE]	= s[C_WERASE];
# endif /* VWERASE */
# ifdef VSUSP
	n->c_cc[VSUSP]		= s[C_SUSP];
# endif /* VSUSP */
# ifdef VDSUSP
	n->c_cc[VDSUSP]		= s[C_DSUSP];
# endif /* VDSUSP */
# ifdef VREPRINT
	n->c_cc[VREPRINT]	= s[C_REPRINT];
# endif /* WREPRINT */
# ifdef VDISCARD
	n->c_cc[VDISCARD]	= s[C_DISCARD];
# endif /* VDISCARD */
# ifdef VLNEXT
	n->c_cc[VLNEXT]		= s[C_LNEXT];
# endif /* VLNEXT */
# ifdef VSTATUS
	n->c_cc[VSTATUS]	= s[C_STATUS];
# endif /* VSTATUS */
# ifdef VPAGE
	n->c_cc[VPAGE]		= s[C_PAGE];
# endif /* VPAGE */
# ifdef VPGOFF
	n->c_cc[VPGOFF]		= s[C_PGOFF];
# endif /* VPGOFF */
# ifdef VKILL2
	n->c_cc[VKILL2]		= s[C_KILL2];
# endif /* VKILL2 */
# ifdef VMIN
	n->c_cc[VMIN]		= s[C_MIN];
# endif /* VMIN */
# ifdef VTIME
	n->c_cc[VTIME]		= s[C_TIME];
# endif /* VTIME */
    }

#else /* GSTTY */

# ifdef TIOCGPAGE
    {
	struct ttypagestat *n = &td->d_pc;

	n->tps_length		= 0;
	n->tps_lpos		= 0;
	n->tps_statc		= s[C_STATUS];
	n->tps_pagec		= s[C_PAGE];
	n->tps_pgoffc		= s[C_PGOFF];
	n->tps_flag		= 0;
    }
# endif /* TIOCGPAGE */

# ifdef TIOCGETC
    {
	struct tchars *n = &td->d_tc;
	n->t_intrc		= s[C_INTR];
	n->t_quitc		= s[C_QUIT];
	n->t_startc		= s[C_START];
	n->t_stopc		= s[C_STOP];
	n->t_eofc		= s[C_EOF];
	n->t_brkc		= s[C_BRK];
    }
# endif /* TIOCGETC */

# ifdef TIOCGETP
    {
	struct sgttyb *n = &td->d_t;

	n->sg_erase		= s[C_ERASE];
	n->sg_kill		= s[C_KILL];
    }
# endif /* TIOCGETP */
#endif /* !POSIX || TERMIO */

}