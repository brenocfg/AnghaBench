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
 scalar_t__ AltKeyMap ; 
 int Argument ; 
 int /*<<< orphan*/  CcKeyMap ; 
 int /*<<< orphan*/  CurrentKeyMap ; 
 int /*<<< orphan*/ * Cursor ; 
 scalar_t__ DoingArg ; 
 int /*<<< orphan*/  F_UNASSIGNED ; 
 scalar_t__ Hist_num ; 
 int INBUFSIZE ; 
 scalar_t__ IncMatchLen ; 
 int /*<<< orphan*/ * InputBuf ; 
 int /*<<< orphan*/ * InputLim ; 
 int /*<<< orphan*/ * LastChar ; 
 int /*<<< orphan*/  LastCmd ; 
 int MacroLvl ; 
 int /*<<< orphan*/ * Mark ; 
 scalar_t__ MarkIsSet ; 
 scalar_t__ MetaNext ; 

void
ResetInLine(int macro)
{
    Cursor = InputBuf;		/* reset cursor */
    LastChar = InputBuf;
    InputLim = &InputBuf[INBUFSIZE - 2];/*FIXBUF*/
    Mark = InputBuf;
    MarkIsSet = 0;
    MetaNext = 0;
    CurrentKeyMap = CcKeyMap;
    AltKeyMap = 0;
    Hist_num = 0;
    DoingArg = 0;
    Argument = 1;
    LastCmd = F_UNASSIGNED;	/* previous command executed */
    IncMatchLen = 0;
    if (macro)
	MacroLvl = -1;		/* no currently active macros */
}