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
 scalar_t__ GoodStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PUTPURE ; 
 int /*<<< orphan*/  Str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T_cd ; 
 int /*<<< orphan*/  T_cl ; 
 int /*<<< orphan*/  T_ho ; 
 int /*<<< orphan*/  T_li ; 
 int /*<<< orphan*/  Val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putraw (char) ; 
 int /*<<< orphan*/  tputs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ClearScreen(void)
{				/* clear the whole screen and home */
    if (GoodStr(T_cl))
	/* send the clear screen code */
	(void) tputs(Str(T_cl), Val(T_li), PUTPURE);
    else if (GoodStr(T_ho) && GoodStr(T_cd)) {
	(void) tputs(Str(T_ho), Val(T_li), PUTPURE);	/* home */
	/* clear to bottom of screen */
	(void) tputs(Str(T_cd), Val(T_li), PUTPURE);
    }
    else {
	(void) putraw('\r');
	(void) putraw('\n');
    }
}