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

/* Variables and functions */
 scalar_t__ Cursor ; 
 scalar_t__ InputLim ; 
 scalar_t__ LastChar ; 
 scalar_t__ Mark ; 

void
c_insert(int num)
{
    Char *cp;

    if (LastChar + num >= InputLim)
	return;			/* can't go past end of buffer */

    if (Cursor < LastChar) {	/* if I must move chars */
	for (cp = LastChar; cp >= Cursor; cp--)
	    cp[num] = *cp;
	if (Mark && Mark > Cursor)
		Mark += num;
    }
    LastChar += num;
}