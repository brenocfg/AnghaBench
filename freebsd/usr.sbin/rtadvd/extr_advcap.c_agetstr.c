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
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int /*<<< orphan*/ ) ; 
 char* tbuf ; 
 char* tdecode (char*,char**) ; 
 char* tskip (char*) ; 

char *
tgetstr(char *id, char **area)
{
	char *bp = tbuf;

	for (;;) {
		bp = tskip(bp);
		if (!*bp)
			return (0);
		if (strncmp(bp, id, strlen(id)) != 0)
			continue;
		bp += strlen(id);
		if (*bp == '@')
			return (0);
		if (*bp != '=')
			continue;
		bp++;
		return (tdecode(bp, area));
	}
}