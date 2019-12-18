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
 int ActionFlag ; 
 scalar_t__ ActionPos ; 
 scalar_t__ Cursor ; 
 int /*<<< orphan*/  RefCursor () ; 
 int TCSHOP_INSERT ; 
 int TCSHOP_NOP ; 
 int UndoAction ; 
 scalar_t__ UndoPtr ; 
 int UndoSize ; 
 int /*<<< orphan*/  c_alternativ_key_map (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_delafter (int) ; 
 int /*<<< orphan*/  c_delbefore (int) ; 

__attribute__((used)) static void
c_delfini(void)		/* Finish up delete action */
{
    int Size;

    if (ActionFlag & TCSHOP_INSERT)
	c_alternativ_key_map(0);

    ActionFlag = TCSHOP_NOP;

    if (ActionPos == 0) 
	return;

    UndoAction = TCSHOP_INSERT;

    if (Cursor > ActionPos) {
	Size = (int) (Cursor-ActionPos);
	c_delbefore(Size); 
	RefCursor();
    }
    else if (Cursor < ActionPos) {
	Size = (int)(ActionPos-Cursor);
	c_delafter(Size);
    }
    else  {
	Size = 1;
	c_delafter(Size);
    }
    UndoPtr = Cursor;
    UndoSize = Size;
}