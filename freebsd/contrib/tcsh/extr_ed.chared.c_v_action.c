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
typedef  int /*<<< orphan*/  Char ;
typedef  int /*<<< orphan*/  CCRETVAL ;

/* Variables and functions */
 int ActionFlag ; 
 void* ActionPos ; 
 int /*<<< orphan*/  CC_ARGHACK ; 
 int /*<<< orphan*/  CC_ERROR ; 
 int /*<<< orphan*/  CC_REFRESH ; 
 void* Cursor ; 
 void* InputBuf ; 
 int /*<<< orphan*/ * LastChar ; 
 int TCSHOP_DELETE ; 
 int TCSHOP_INSERT ; 
 int TCSHOP_NOP ; 
 int UndoAction ; 
 int /*<<< orphan*/ * UndoBuf ; 
 void* UndoPtr ; 
 scalar_t__ UndoSize ; 
 int /*<<< orphan*/  c_alternativ_key_map (int /*<<< orphan*/ ) ; 

__attribute__((used)) static CCRETVAL
v_action(int c)
{
    Char *cp, *kp;

    if (ActionFlag == TCSHOP_DELETE) {
	ActionFlag = TCSHOP_NOP;
	ActionPos = 0;
	
	UndoSize = 0;
	kp = UndoBuf;
	for (cp = InputBuf; cp < LastChar; cp++) {
	    *kp++ = *cp;
	    UndoSize++;
	}
		
	UndoAction = TCSHOP_INSERT;
	UndoPtr  = InputBuf;
	LastChar = InputBuf;
	Cursor   = InputBuf;
	if (c & TCSHOP_INSERT)
	    c_alternativ_key_map(0);
	    
	return(CC_REFRESH);
    }
#ifdef notdef
    else if (ActionFlag == TCSHOP_NOP) {
#endif
	ActionPos = Cursor;
	ActionFlag = c;
	return(CC_ARGHACK);  /* Do NOT clear out argument */
#ifdef notdef
    }
    else {
	ActionFlag = 0;
	ActionPos = 0;
	return(CC_ERROR);
    }
#endif
}