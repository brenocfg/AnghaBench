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
struct headline {int /*<<< orphan*/ * l_date; } ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  fail (char*,char*) ; 
 int /*<<< orphan*/  isdate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse (char*,struct headline*,char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

int
ishead(char linebuf[])
{
	struct headline hl;
	char parbuf[BUFSIZ];

	if (strncmp(linebuf, "From ", 5) != 0)
		return (0);
	parse(linebuf, &hl, parbuf);
	if (hl.l_date == NULL) {
		fail(linebuf, "No date field");
		return (0);
	}
	if (!isdate(hl.l_date)) {
		fail(linebuf, "Date field not legal date");
		return (0);
	}
	/*
	 * I guess we got it!
	 */
	return (1);
}