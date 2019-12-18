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
tty__getchar(struct termios *td, unsigned char *s)
{

#ifdef VINTR
	s[C_INTR] = td->c_cc[VINTR];
#endif /* VINTR */
#ifdef VQUIT
	s[C_QUIT] = td->c_cc[VQUIT];
#endif /* VQUIT */
#ifdef VERASE
	s[C_ERASE] = td->c_cc[VERASE];
#endif /* VERASE */
#ifdef VKILL
	s[C_KILL] = td->c_cc[VKILL];
#endif /* VKILL */
#ifdef VEOF
	s[C_EOF] = td->c_cc[VEOF];
#endif /* VEOF */
#ifdef VEOL
	s[C_EOL] = td->c_cc[VEOL];
#endif /* VEOL */
#ifdef VEOL2
	s[C_EOL2] = td->c_cc[VEOL2];
#endif /* VEOL2 */
#ifdef VSWTCH
	s[C_SWTCH] = td->c_cc[VSWTCH];
#endif /* VSWTCH */
#ifdef VDSWTCH
	s[C_DSWTCH] = td->c_cc[VDSWTCH];
#endif /* VDSWTCH */
#ifdef VERASE2
	s[C_ERASE2] = td->c_cc[VERASE2];
#endif /* VERASE2 */
#ifdef VSTART
	s[C_START] = td->c_cc[VSTART];
#endif /* VSTART */
#ifdef VSTOP
	s[C_STOP] = td->c_cc[VSTOP];
#endif /* VSTOP */
#ifdef VWERASE
	s[C_WERASE] = td->c_cc[VWERASE];
#endif /* VWERASE */
#ifdef VSUSP
	s[C_SUSP] = td->c_cc[VSUSP];
#endif /* VSUSP */
#ifdef VDSUSP
	s[C_DSUSP] = td->c_cc[VDSUSP];
#endif /* VDSUSP */
#ifdef VREPRINT
	s[C_REPRINT] = td->c_cc[VREPRINT];
#endif /* VREPRINT */
#ifdef VDISCARD
	s[C_DISCARD] = td->c_cc[VDISCARD];
#endif /* VDISCARD */
#ifdef VLNEXT
	s[C_LNEXT] = td->c_cc[VLNEXT];
#endif /* VLNEXT */
#ifdef VSTATUS
	s[C_STATUS] = td->c_cc[VSTATUS];
#endif /* VSTATUS */
#ifdef VPAGE
	s[C_PAGE] = td->c_cc[VPAGE];
#endif /* VPAGE */
#ifdef VPGOFF
	s[C_PGOFF] = td->c_cc[VPGOFF];
#endif /* VPGOFF */
#ifdef VKILL2
	s[C_KILL2] = td->c_cc[VKILL2];
#endif /* KILL2 */
#ifdef VMIN
	s[C_MIN] = td->c_cc[VMIN];
#endif /* VMIN */
#ifdef VTIME
	s[C_TIME] = td->c_cc[VTIME];
#endif /* VTIME */
}