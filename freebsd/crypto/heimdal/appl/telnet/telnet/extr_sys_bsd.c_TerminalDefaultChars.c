#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  c_cc; } ;
struct TYPE_3__ {int /*<<< orphan*/  c_cc; } ;

/* Variables and functions */
 void* CONTROL (char) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_2__ new_tc ; 
 TYPE_1__ old_tc ; 
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
    memmove(new_tc.c_cc, old_tc.c_cc, sizeof(old_tc.c_cc));
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
}