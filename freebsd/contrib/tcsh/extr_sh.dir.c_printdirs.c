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
struct directory {int /*<<< orphan*/ * di_name; struct directory* di_prev; } ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int DIR_LINE ; 
 int DIR_LONG ; 
 int DIR_VERT ; 
 scalar_t__ Strlen (int /*<<< orphan*/ *) ; 
 int TermH ; 
 struct directory* dcwd ; 
 struct directory dhead ; 
 int /*<<< orphan*/ * getusername (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  xprintf (char*,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  xputchar (char) ; 

__attribute__((used)) static void
printdirs(int dflag)
{
    struct directory *dp;
    Char   *s, *user;
    int     idx, len, cur;

    dp = dcwd;
    idx = 0;
    cur = 0;
    do {
	if (dp == &dhead)
	    continue;
	if (dflag & DIR_VERT) {
	    xprintf("%d\t", idx++);
	    cur = 0;
	}
	s = dp->di_name;		
	user = NULL;
	if (!(dflag & DIR_LONG) && (user = getusername(&s)) != NULL)
	    len = (int) (Strlen(user) + Strlen(s) + 2);
	else
	    len = (int) (Strlen(s) + 1);

	cur += len;
	if ((dflag & DIR_LINE) && cur >= TermH - 1 && len < TermH) {
	    xputchar('\n');
	    cur = len;
	}
	if (user) 
	    xprintf("~%S", user);
	xprintf("%-S%c", s, (dflag & DIR_VERT) ? '\n' : ' ');
    } while ((dp = dp->di_prev) != dcwd);
    if (!(dflag & DIR_VERT))
	xputchar('\n');
}