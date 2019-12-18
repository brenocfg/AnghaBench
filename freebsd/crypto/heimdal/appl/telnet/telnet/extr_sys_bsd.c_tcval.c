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
typedef  int /*<<< orphan*/  cc_t ;

/* Variables and functions */
#define  SLC_ABORT 145 
#define  SLC_AO 144 
#define  SLC_AYT 143 
#define  SLC_BRK 142 
#define  SLC_EC 141 
#define  SLC_EL 140 
#define  SLC_EOF 139 
#define  SLC_EOR 138 
#define  SLC_EW 137 
#define  SLC_FORW1 136 
#define  SLC_FORW2 135 
#define  SLC_IP 134 
#define  SLC_LNEXT 133 
#define  SLC_RP 132 
#define  SLC_SUSP 131 
#define  SLC_SYNCH 130 
#define  SLC_XOFF 129 
#define  SLC_XON 128 
 int /*<<< orphan*/  termAytChar ; 
 int /*<<< orphan*/  termEofChar ; 
 int /*<<< orphan*/  termEraseChar ; 
 int /*<<< orphan*/  termFlushChar ; 
 int /*<<< orphan*/  termForw1Char ; 
 int /*<<< orphan*/  termForw2Char ; 
 int /*<<< orphan*/  termIntChar ; 
 int /*<<< orphan*/  termKillChar ; 
 int /*<<< orphan*/  termLiteralNextChar ; 
 int /*<<< orphan*/  termQuitChar ; 
 int /*<<< orphan*/  termRprntChar ; 
 int /*<<< orphan*/  termStartChar ; 
 int /*<<< orphan*/  termStopChar ; 
 int /*<<< orphan*/  termSuspChar ; 
 int /*<<< orphan*/  termWerasChar ; 

cc_t*
tcval(int func)
{
    switch(func) {
    case SLC_IP:	return(&termIntChar);
    case SLC_ABORT:	return(&termQuitChar);
    case SLC_EOF:	return(&termEofChar);
    case SLC_EC:	return(&termEraseChar);
    case SLC_EL:	return(&termKillChar);
    case SLC_XON:	return(&termStartChar);
    case SLC_XOFF:	return(&termStopChar);
    case SLC_FORW1:	return(&termForw1Char);
    case SLC_FORW2:	return(&termForw2Char);
# ifdef	VDISCARD
    case SLC_AO:	return(&termFlushChar);
# endif
# ifdef	VSUSP
    case SLC_SUSP:	return(&termSuspChar);
# endif
# ifdef	VWERASE
    case SLC_EW:	return(&termWerasChar);
# endif
# ifdef	VREPRINT
    case SLC_RP:	return(&termRprntChar);
# endif
# ifdef	VLNEXT
    case SLC_LNEXT:	return(&termLiteralNextChar);
# endif
# ifdef	VSTATUS
    case SLC_AYT:	return(&termAytChar);
# endif

    case SLC_SYNCH:
    case SLC_BRK:
    case SLC_EOR:
    default:
	return((cc_t *)0);
    }
}