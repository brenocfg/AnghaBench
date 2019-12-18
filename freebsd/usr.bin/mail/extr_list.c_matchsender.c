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
 int /*<<< orphan*/ * message ; 
 char* nameof (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strcasestr (char*,char*) ; 

int
matchsender(char *str, int mesg)
{
	char *cp;

	/* null string matches nothing instead of everything */
	if (*str == '\0')
		return (0);

	cp = nameof(&message[mesg - 1], 0);
	return (strcasestr(cp, str) != NULL);
}