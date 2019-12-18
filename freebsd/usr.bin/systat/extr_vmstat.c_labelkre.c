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
 int /*<<< orphan*/  DISKCOL ; 
 int /*<<< orphan*/  DISKROW ; 
 int /*<<< orphan*/  GENSTATCOL ; 
 int /*<<< orphan*/  GENSTATROW ; 
 int /*<<< orphan*/  GRAPHCOL ; 
 scalar_t__ GRAPHROW ; 
 scalar_t__ INTSCOL ; 
 scalar_t__ INTSROW ; 
 int LINES ; 
 int /*<<< orphan*/  MAXDRIVES ; 
 scalar_t__ MEMCOL ; 
 scalar_t__ MEMROW ; 
 int /*<<< orphan*/  NAMEICOL ; 
 scalar_t__ NAMEIROW ; 
 int /*<<< orphan*/  PAGECOL ; 
 scalar_t__ PAGEROW ; 
 int /*<<< orphan*/  PROCSCOL ; 
 scalar_t__ PROCSROW ; 
 scalar_t__ STATCOL ; 
 scalar_t__ STATROW ; 
 scalar_t__ VMSTATCOL ; 
 int VMSTATROW ; 
 scalar_t__ VNSTATCOL ; 
 scalar_t__ VNSTATROW ; 
 int /*<<< orphan*/  clear () ; 
 int /*<<< orphan*/  dslabel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__* intrloc ; 
 int /*<<< orphan*/ * intrname ; 
 int /*<<< orphan*/  mvprintw (scalar_t__,scalar_t__,char*,...) ; 
 int nintr ; 

void
labelkre(void)
{
	int i, j;

	clear();
	mvprintw(STATROW, STATCOL + 6, "users    Load");
	mvprintw(STATROW + 1, STATCOL + 3, "Mem usage:    %%Phy   %%Kmem");
	mvprintw(MEMROW, MEMCOL, "Mem: KB    REAL            VIRTUAL");
	mvprintw(MEMROW + 1, MEMCOL, "        Tot   Share      Tot    Share");
	mvprintw(MEMROW + 2, MEMCOL, "Act");
	mvprintw(MEMROW + 3, MEMCOL, "All");

	mvprintw(MEMROW + 1, MEMCOL + 41, "Free");

	mvprintw(PAGEROW, PAGECOL,     "         VN PAGER   SWAP PAGER");
	mvprintw(PAGEROW + 1, PAGECOL, "         in   out     in   out");
	mvprintw(PAGEROW + 2, PAGECOL, "count");
	mvprintw(PAGEROW + 3, PAGECOL, "pages");

	mvprintw(INTSROW, INTSCOL + 1, "Interrupts");
	mvprintw(INTSROW + 1, INTSCOL + 6, "total");

	mvprintw(VMSTATROW, VMSTATCOL + 9, "ioflt");
	mvprintw(VMSTATROW + 1, VMSTATCOL + 9, "cow");
	mvprintw(VMSTATROW + 2, VMSTATCOL + 9, "zfod");
	mvprintw(VMSTATROW + 3, VMSTATCOL + 9, "ozfod");
	mvprintw(VMSTATROW + 4, VMSTATCOL + 9 - 1, "%%ozfod");
	mvprintw(VMSTATROW + 5, VMSTATCOL + 9, "daefr");
	mvprintw(VMSTATROW + 6, VMSTATCOL + 9, "prcfr");
	mvprintw(VMSTATROW + 7, VMSTATCOL + 9, "totfr");
	mvprintw(VMSTATROW + 8, VMSTATCOL + 9, "react");
	mvprintw(VMSTATROW + 9, VMSTATCOL + 9, "pdwak");
	mvprintw(VMSTATROW + 10, VMSTATCOL + 9, "pdpgs");
	mvprintw(VMSTATROW + 11, VMSTATCOL + 9, "intrn");
	mvprintw(VMSTATROW + 12, VMSTATCOL + 9, "wire");
	mvprintw(VMSTATROW + 13, VMSTATCOL + 9, "act");
	mvprintw(VMSTATROW + 14, VMSTATCOL + 9, "inact");
	mvprintw(VMSTATROW + 15, VMSTATCOL + 9, "laund");
	mvprintw(VMSTATROW + 16, VMSTATCOL + 9, "free");
	if (LINES - 1 > VMSTATROW + 17)
		mvprintw(VMSTATROW + 17, VMSTATCOL + 9, "buf");

	mvprintw(GENSTATROW, GENSTATCOL, " Csw  Trp  Sys  Int  Sof  Flt");

	mvprintw(GRAPHROW, GRAPHCOL,
		"  . %%Sys    . %%Intr   . %%User   . %%Nice   . %%Idle");
	mvprintw(PROCSROW, PROCSCOL, "Proc:");
	mvprintw(PROCSROW + 1, PROCSCOL, "  r   p   d   s   w");
	mvprintw(GRAPHROW + 1, GRAPHCOL,
		"|    |    |    |    |    |    |    |    |    |    |");

	mvprintw(VNSTATROW, VNSTATCOL + 8, "dtbuf");
	mvprintw(VNSTATROW + 1, VNSTATCOL + 8, "desvn");
	mvprintw(VNSTATROW + 2, VNSTATCOL + 8, "numvn");
	mvprintw(VNSTATROW + 3, VNSTATCOL + 8, "frevn");

	mvprintw(NAMEIROW, NAMEICOL, "Namei     Name-cache   Dir-cache");
	mvprintw(NAMEIROW + 1, NAMEICOL,
		"   Calls    hits   %%    hits   %%");
	dslabel(MAXDRIVES, DISKCOL, DISKROW);

	for (i = 0; i < nintr; i++) {
		if (intrloc[i] == 0)
			continue;
		mvprintw(intrloc[i], INTSCOL + 6, "%-10.10s", intrname[i]);
	}
}