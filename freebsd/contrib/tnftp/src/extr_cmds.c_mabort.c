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
 scalar_t__ confirm (char const*,int /*<<< orphan*/ *) ; 
 int confirmrest ; 
 scalar_t__ fromatty ; 
 int interactive ; 
 scalar_t__ mflag ; 

__attribute__((used)) static void
mabort(const char *cmd)
{
	int ointer, oconf;

	if (mflag && fromatty) {
		ointer = interactive;
		oconf = confirmrest;
		interactive = 1;
		confirmrest = 0;
		if (confirm(cmd, NULL)) {
			interactive = ointer;
			confirmrest = oconf;
			return;
		}
		interactive = ointer;
		confirmrest = oconf;
	}
	mflag = 0;
}