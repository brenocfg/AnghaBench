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
struct termios {unsigned char* c_cc; } ;

/* Variables and functions */
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

__attribute__((used)) static void
tty__setchar(struct termios *td, unsigned char *s)
{

#ifdef VINTR
	td->c_cc[VINTR] = s[C_INTR];
#endif /* VINTR */
#ifdef VQUIT
	td->c_cc[VQUIT] = s[C_QUIT];
#endif /* VQUIT */
#ifdef VERASE
	td->c_cc[VERASE] = s[C_ERASE];
#endif /* VERASE */
#ifdef VKILL
	td->c_cc[VKILL] = s[C_KILL];
#endif /* VKILL */
#ifdef VEOF
	td->c_cc[VEOF] = s[C_EOF];
#endif /* VEOF */
#ifdef VEOL
	td->c_cc[VEOL] = s[C_EOL];
#endif /* VEOL */
#ifdef VEOL2
	td->c_cc[VEOL2] = s[C_EOL2];
#endif /* VEOL2 */
#ifdef VSWTCH
	td->c_cc[VSWTCH] = s[C_SWTCH];
#endif /* VSWTCH */
#ifdef VDSWTCH
	td->c_cc[VDSWTCH] = s[C_DSWTCH];
#endif /* VDSWTCH */
#ifdef VERASE2
	td->c_cc[VERASE2] = s[C_ERASE2];
#endif /* VERASE2 */
#ifdef VSTART
	td->c_cc[VSTART] = s[C_START];
#endif /* VSTART */
#ifdef VSTOP
	td->c_cc[VSTOP] = s[C_STOP];
#endif /* VSTOP */
#ifdef VWERASE
	td->c_cc[VWERASE] = s[C_WERASE];
#endif /* VWERASE */
#ifdef VSUSP
	td->c_cc[VSUSP] = s[C_SUSP];
#endif /* VSUSP */
#ifdef VDSUSP
	td->c_cc[VDSUSP] = s[C_DSUSP];
#endif /* VDSUSP */
#ifdef VREPRINT
	td->c_cc[VREPRINT] = s[C_REPRINT];
#endif /* VREPRINT */
#ifdef VDISCARD
	td->c_cc[VDISCARD] = s[C_DISCARD];
#endif /* VDISCARD */
#ifdef VLNEXT
	td->c_cc[VLNEXT] = s[C_LNEXT];
#endif /* VLNEXT */
#ifdef VSTATUS
	td->c_cc[VSTATUS] = s[C_STATUS];
#endif /* VSTATUS */
#ifdef VPAGE
	td->c_cc[VPAGE] = s[C_PAGE];
#endif /* VPAGE */
#ifdef VPGOFF
	td->c_cc[VPGOFF] = s[C_PGOFF];
#endif /* VPGOFF */
#ifdef VKILL2
	td->c_cc[VKILL2] = s[C_KILL2];
#endif /* VKILL2 */
#ifdef VMIN
	td->c_cc[VMIN] = s[C_MIN];
#endif /* VMIN */
#ifdef VTIME
	td->c_cc[VTIME] = s[C_TIME];
#endif /* VTIME */
}