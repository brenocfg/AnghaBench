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
 int /*<<< orphan*/  CTL_ESC (char) ; 
 scalar_t__ GoodStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PUTPURE ; 
 int /*<<< orphan*/  STRnobeep ; 
 int /*<<< orphan*/  STRvisiblebell ; 
 int /*<<< orphan*/  Str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T_bl ; 
 int /*<<< orphan*/  T_vb ; 
 scalar_t__ adrof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  beep_cmd () ; 
 int /*<<< orphan*/  putraw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tputs (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void
SoundBeep(void)
{				/* produce a sound */
    beep_cmd ();
    if (adrof(STRnobeep))
	return;

    if (GoodStr(T_vb) && adrof(STRvisiblebell))
	(void) tputs(Str(T_vb), 1, PUTPURE);	/* visible bell */
    else if (GoodStr(T_bl))
	/* what termcap says we should use */
	(void) tputs(Str(T_bl), 1, PUTPURE);
    else
	(void) putraw(CTL_ESC('\007'));	/* an ASCII bell; ^G */
}