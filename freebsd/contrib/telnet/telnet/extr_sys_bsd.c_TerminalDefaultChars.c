#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  c_cc; } ;
struct TYPE_7__ {int /*<<< orphan*/  sg_erase; int /*<<< orphan*/  sg_kill; } ;
struct TYPE_6__ {int /*<<< orphan*/  c_cc; } ;
struct TYPE_5__ {int /*<<< orphan*/  sg_erase; int /*<<< orphan*/  sg_kill; } ;

/* Variables and functions */
 void* CONTROL (char) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_4__ new_tc ; 
 int /*<<< orphan*/  nltc ; 
 int /*<<< orphan*/  ntc ; 
 TYPE_3__ nttyb ; 
 TYPE_2__ old_tc ; 
 int /*<<< orphan*/  oltc ; 
 int /*<<< orphan*/  otc ; 
 TYPE_1__ ottyb ; 
 void* termAytChar ; 
 void* termFlushChar ; 
 void* termLiteralNextChar ; 
 void* termRprntChar ; 
 void* termStartChar ; 
 void* termStopChar ; 
 void* termWerasChar ; 

void
TerminalDefaultChars(void)
{
#ifndef	USE_TERMIO
    ntc = otc;
    nltc = oltc;
    nttyb.sg_kill = ottyb.sg_kill;
    nttyb.sg_erase = ottyb.sg_erase;
#else	/* USE_TERMIO */
    memcpy(new_tc.c_cc, old_tc.c_cc, sizeof(old_tc.c_cc));
# ifndef	VDISCARD
    termFlushChar = CONTROL('O');
# endif
# ifndef	VWERASE
    termWerasChar = CONTROL('W');
# endif
# ifndef	VREPRINT
    termRprntChar = CONTROL('R');
# endif
# ifndef	VLNEXT
    termLiteralNextChar = CONTROL('V');
# endif
# ifndef	VSTART
    termStartChar = CONTROL('Q');
# endif
# ifndef	VSTOP
    termStopChar = CONTROL('S');
# endif
# ifndef	VSTATUS
    termAytChar = CONTROL('T');
# endif
#endif	/* USE_TERMIO */
}