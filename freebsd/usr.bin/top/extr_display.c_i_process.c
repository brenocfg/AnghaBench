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
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ lastline ; 
 int lineindex (int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int screen_width ; 
 char* screenbuf ; 
 scalar_t__ smart_terminal ; 
 int /*<<< orphan*/  stdout ; 
 char* stpcpy (char*,char*) ; 
 int strlen (char*) ; 
 scalar_t__ y_procs ; 

void
i_process(int line, char *thisline)
{
    char *p;
    char *base;

    /* make sure we are on the correct line */
    while (lastline < y_procs + line)
    {
	putchar('\n');
	lastline++;
    }

    /* truncate the line to conform to our current screen width */
    int len = strlen(thisline);
    if (screen_width < len)
    {
	thisline[screen_width] = '\0';
    }

    /* write the line out */
    fputs(thisline, stdout);

    /* copy it in to our buffer */
    base = smart_terminal ? screenbuf + lineindex(line) : screenbuf;
    p = stpcpy(base, thisline);

    /* zero fill the rest of it */
    if (p - base < screen_width)
    {
	memset(p, 0, screen_width - (p - base));
    }
}