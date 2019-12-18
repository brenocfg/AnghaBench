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

/* Variables and functions */
#define  C_DISCARD 151 
#define  C_DSUSP 150 
#define  C_DSWTCH 149 
#define  C_EOF 148 
#define  C_EOL 147 
#define  C_EOL2 146 
#define  C_ERASE 145 
#define  C_ERASE2 144 
#define  C_INTR 143 
#define  C_KILL 142 
#define  C_KILL2 141 
#define  C_LNEXT 140 
#define  C_MIN 139 
#define  C_PAGE 138 
#define  C_PGOFF 137 
#define  C_QUIT 136 
#define  C_REPRINT 135 
#define  C_START 134 
#define  C_STATUS 133 
#define  C_STOP 132 
#define  C_SUSP 131 
#define  C_SWTCH 130 
#define  C_TIME 129 
#define  C_WERASE 128 
 int VDISCARD ; 
 int VDSUSP ; 
 int VDSWTCH ; 
 int VEOF ; 
 int VEOL ; 
 int VEOL2 ; 
 int VERASE ; 
 int VERASE2 ; 
 int VINTR ; 
 int VKILL ; 
 int VKILL2 ; 
 int VLNEXT ; 
 int VMIN ; 
 int VPAGE ; 
 int VPGOFF ; 
 int VQUIT ; 
 int VREPRINT ; 
 int VSTART ; 
 int VSTATUS ; 
 int VSTOP ; 
 int VSUSP ; 
 int VSWTCH ; 
 int VTIME ; 
 int VWERASE ; 

__attribute__((used)) static int
tty__getcharindex(int i)
{
	switch (i) {
#ifdef VINTR
	case C_INTR:
		return VINTR;
#endif /* VINTR */
#ifdef VQUIT
	case C_QUIT:
		return VQUIT;
#endif /* VQUIT */
#ifdef VERASE
	case C_ERASE:
		return VERASE;
#endif /* VERASE */
#ifdef VKILL
	case C_KILL:
		return VKILL;
#endif /* VKILL */
#ifdef VEOF
	case C_EOF:
		return VEOF;
#endif /* VEOF */
#ifdef VEOL
	case C_EOL:
		return VEOL;
#endif /* VEOL */
#ifdef VEOL2
	case C_EOL2:
		return VEOL2;
#endif /* VEOL2 */
#ifdef VSWTCH
	case C_SWTCH:
		return VSWTCH;
#endif /* VSWTCH */
#ifdef VDSWTCH
	case C_DSWTCH:
		return VDSWTCH;
#endif /* VDSWTCH */
#ifdef VERASE2
	case C_ERASE2:
		return VERASE2;
#endif /* VERASE2 */
#ifdef VSTART
	case C_START:
		return VSTART;
#endif /* VSTART */
#ifdef VSTOP
	case C_STOP:
		return VSTOP;
#endif /* VSTOP */
#ifdef VWERASE
	case C_WERASE:
		return VWERASE;
#endif /* VWERASE */
#ifdef VSUSP
	case C_SUSP:
		return VSUSP;
#endif /* VSUSP */
#ifdef VDSUSP
	case C_DSUSP:
		return VDSUSP;
#endif /* VDSUSP */
#ifdef VREPRINT
	case C_REPRINT:
		return VREPRINT;
#endif /* VREPRINT */
#ifdef VDISCARD
	case C_DISCARD:
		return VDISCARD;
#endif /* VDISCARD */
#ifdef VLNEXT
	case C_LNEXT:
		return VLNEXT;
#endif /* VLNEXT */
#ifdef VSTATUS
	case C_STATUS:
		return VSTATUS;
#endif /* VSTATUS */
#ifdef VPAGE
	case C_PAGE:
		return VPAGE;
#endif /* VPAGE */
#ifdef VPGOFF
	case C_PGOFF:
		return VPGOFF;
#endif /* VPGOFF */
#ifdef VKILL2
	case C_KILL2:
		return VKILL2;
#endif /* KILL2 */
#ifdef VMIN
	case C_MIN:
		return VMIN;
#endif /* VMIN */
#ifdef VTIME
	case C_TIME:
		return VTIME;
#endif /* VTIME */
	default:
		return -1;
	}
}