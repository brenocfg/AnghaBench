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
 int CursorH ; 
 scalar_t__ GoodStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PUTPURE ; 
 int /*<<< orphan*/  Str (int /*<<< orphan*/ ) ; 
 scalar_t__ T_CanCEOL ; 
 int /*<<< orphan*/  T_ce ; 
 int /*<<< orphan*/  putraw (char) ; 
 int /*<<< orphan*/  tputs (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void
ClearEOL(int num)
{
    int i;

    if (num <= 0)
	return;

    if (T_CanCEOL && GoodStr(T_ce))
	(void) tputs(Str(T_ce), 1, PUTPURE);
    else {
	for (i = 0; i < num; i++)
	    (void) putraw(' ');
	CursorH += num;		/* have written num spaces */
    }
}