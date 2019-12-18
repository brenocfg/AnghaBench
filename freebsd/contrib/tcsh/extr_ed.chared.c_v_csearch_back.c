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
typedef  scalar_t__ Char ;
typedef  int /*<<< orphan*/  CCRETVAL ;

/* Variables and functions */
 int ActionFlag ; 
 int /*<<< orphan*/  CC_ERROR ; 
 int /*<<< orphan*/  CC_NORM ; 
 int /*<<< orphan*/  CC_REFRESH ; 
 scalar_t__* Cursor ; 
 scalar_t__* InputBuf ; 
 int /*<<< orphan*/  RefCursor () ; 
 int TCSHOP_DELETE ; 
 int /*<<< orphan*/  c_delfini () ; 

__attribute__((used)) static CCRETVAL
v_csearch_back(Char ch, int count, int tflag)
{
    Char *cp;

    cp = Cursor;
    while (count--) {
	if (*cp == ch) 
	    cp--;
	while (cp > InputBuf && *cp != ch) 
	    cp--;
    }

    if (cp < InputBuf || (cp == InputBuf && *cp != ch))
	return(CC_ERROR);

    if (*cp == ch && tflag)
	cp++;

    Cursor = cp;

    if (ActionFlag & TCSHOP_DELETE) {
	Cursor++;
	c_delfini();
	return(CC_REFRESH);
    }

    RefCursor();
    return(CC_NORM);
}