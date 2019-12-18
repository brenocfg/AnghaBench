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
 int Header_lines ; 
 int /*<<< orphan*/  Move_to (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int last_hi ; 
 int lastline ; 
 int /*<<< orphan*/  line_update (char*,char*,int /*<<< orphan*/ ,int) ; 
 size_t lineindex (int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int screen_width ; 
 char* screenbuf ; 
 int /*<<< orphan*/  stdout ; 
 char* stpcpy (char*,char*) ; 
 int strlen (char*) ; 

void
u_process(int line, char *newline)
{
    char *optr;
    int screen_line = line + Header_lines;
    char *bufferline;

    /* remember a pointer to the current line in the screen buffer */
    bufferline = &screenbuf[lineindex(line)];

    /* truncate the line to conform to our current screen width */
    int len = strlen(newline);
    if (screen_width < len)
    {
	newline[screen_width] = '\0';
    }

    /* is line higher than we went on the last display? */
    if (line >= last_hi)
    {
	/* yes, just ignore screenbuf and write it out directly */
	/* get positioned on the correct line */
	if (screen_line - lastline == 1)
	{
	    putchar('\n');
	    lastline++;
	}
	else
	{
	    Move_to(0, screen_line);
	    lastline = screen_line;
	}

	/* now write the line */
	fputs(newline, stdout);

	/* copy it in to the buffer */
	optr = stpcpy(bufferline, newline);

	/* zero fill the rest of it */
	if (optr - bufferline < screen_width)
	{
	    memset(optr, 0, screen_width - (optr - bufferline));
	}
    }
    else
    {
	line_update(bufferline, newline, 0, line + Header_lines);
    }
}