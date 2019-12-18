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
 scalar_t__ EOF ; 
 int altered ; 
 int blankcount ; 
 int blankmax ; 
 int /*<<< orphan*/  closeio () ; 
 scalar_t__ compblank ; 
 int complement ; 
 scalar_t__ debugging ; 
 scalar_t__ delcount ; 
 scalar_t__ fflush (int /*<<< orphan*/ ) ; 
 scalar_t__ fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashline () ; 
 scalar_t__ lnblank ; 
 scalar_t__ lnnum ; 
 char* newline ; 
 int /*<<< orphan*/  output ; 
 size_t strspn (char*,char*) ; 
 scalar_t__ symlist ; 
 char* tline ; 

__attribute__((used)) static void
flushline(bool keep)
{
	if (symlist)
		return;
	if (keep ^ complement) {
		bool blankline = tline[strspn(tline, " \t\r\n")] == '\0';
		if (blankline && compblank && blankcount != blankmax) {
			delcount += 1;
			blankcount += 1;
		} else {
			if (lnnum && delcount > 0)
				hashline();
			if (fputs(tline, output) == EOF)
				closeio();
			delcount = 0;
			blankmax = blankcount = blankline ? blankcount + 1 : 0;
		}
	} else {
		if (lnblank && fputs(newline, output) == EOF)
			closeio();
		altered = true;
		delcount += 1;
		blankcount = 0;
	}
	if (debugging && fflush(output) == EOF)
		closeio();
}