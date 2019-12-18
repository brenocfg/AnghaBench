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
struct ttypagestat {unsigned char tps_statc; unsigned char tps_pagec; unsigned char tps_pgoffc; } ;
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
tty_getchar(ttydata_t *td, unsigned char *s)
{   
#ifdef TIOCGLTC
    {
	struct ltchars *n = &td->d_ltc;

	s[C_SUSP]	= n->t_suspc;
	s[C_DSUSP]	= n->t_dsuspc;
	s[C_REPRINT]	= n->t_rprntc;
	s[C_DISCARD]	= n->t_flushc;
	s[C_WERASE]	= n->t_werasc;
	s[C_LNEXT]	= n->t_lnextc;
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
	s[C_INTR]	= n->c_cc[VINTR];
# endif /* VINTR */
# ifdef VQUIT
	s[C_QUIT]	= n->c_cc[VQUIT];
# endif /* VQUIT */
# ifdef VERASE
	s[C_ERASE]	= n->c_cc[VERASE];
# endif /* VERASE */
# ifdef VKILL
	s[C_KILL]	= n->c_cc[VKILL];
# endif /* VKILL */
# ifdef VEOF
	s[C_EOF]	= n->c_cc[VEOF];
# endif /* VEOF */
# ifdef VEOL
	s[C_EOL]	= n->c_cc[VEOL];
# endif /* VEOL */
# ifdef VEOL2
	s[C_EOL2]	= n->c_cc[VEOL2];
# endif  /* VEOL2 */
# ifdef VSWTCH
	s[C_SWTCH]	= n->c_cc[VSWTCH];
# endif /* VSWTCH */
# ifdef VDSWTCH
	s[C_DSWTCH]	= n->c_cc[VDSWTCH];
# endif /* VDSWTCH */
# ifdef VERASE2
	s[C_ERASE2]	= n->c_cc[VERASE2];
# endif /* VERASE2 */
# ifdef VSTART
	s[C_START]	= n->c_cc[VSTART];
# endif /* VSTART */
# ifdef VSTOP
	s[C_STOP]	= n->c_cc[VSTOP];
# endif /* VSTOP */
# ifdef VWERASE
	s[C_WERASE]	= n->c_cc[VWERASE];
# endif /* VWERASE */
# ifdef VSUSP
	s[C_SUSP]	= n->c_cc[VSUSP];
# endif /* VSUSP */
# ifdef VDSUSP
	s[C_DSUSP]	= n->c_cc[VDSUSP];
# endif /* VDSUSP */
# ifdef VREPRINT
	s[C_REPRINT]	= n->c_cc[VREPRINT];
# endif /* WREPRINT */
# ifdef VDISCARD
	s[C_DISCARD]	= n->c_cc[VDISCARD];
# endif /* VDISCARD */
# ifdef VLNEXT
	s[C_LNEXT]	= n->c_cc[VLNEXT];
# endif /* VLNEXT */
# ifdef VSTATUS
	s[C_STATUS]	= n->c_cc[VSTATUS];
# endif /* VSTATUS */
# ifdef VPAGE
	s[C_PAGE]	= n->c_cc[VPAGE];
# endif /* VPAGE */
# ifdef VPGOFF
	s[C_PGOFF]	= n->c_cc[VPGOFF];
# endif /* VPGOFF */
# ifdef VKILL2
	s[C_KILL2]	= n->c_cc[VKILL2];
# endif /* KILL2 */
# ifdef VMIN
	s[C_MIN]	= n->c_cc[VMIN];
# endif /* VMIN */
# ifdef VTIME
	s[C_TIME]	= n->c_cc[VTIME];
# endif /* VTIME */
    }

#else /* SGTTY */

# ifdef TIOCGPAGE
    {
	struct ttypagestat *n = &td->d_pc;

	s[C_STATUS]	= n->tps_statc;
	s[C_PAGE]	= n->tps_pagec;
	s[C_PGOFF]	= n->tps_pgoffc;
    }
# endif /* TIOCGPAGE */

# ifdef TIOCGETC
    {
	struct tchars *n = &td->d_tc;

	s[C_INTR]	= n->t_intrc;
	s[C_QUIT]	= n->t_quitc;
	s[C_START]	= n->t_startc;
	s[C_STOP]	= n->t_stopc;
	s[C_EOF]	= n->t_eofc;
	s[C_BRK]	= n->t_brkc;
    }
# endif /* TIOCGETC */

# ifdef TIOCGETP
    {
	struct sgttyb *n = &td->d_t;

	s[C_ERASE]	= n->sg_erase;
	s[C_KILL]	= n->sg_kill;
    }
# endif /* TIOCGETP */
#endif /* !POSIX || TERMIO */

}