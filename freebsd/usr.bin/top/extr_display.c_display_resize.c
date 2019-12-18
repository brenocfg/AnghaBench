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
 int Largest ; 
 int /*<<< orphan*/ * calloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int screen_length ; 
 int /*<<< orphan*/  screen_width ; 
 int /*<<< orphan*/ * screenbuf ; 
 scalar_t__ smart_terminal ; 

int
display_resize(void)
{
    int lines;

    /* first, deallocate any previous buffer that may have been there */
    if (screenbuf != NULL)
    {
	free(screenbuf);
    }

    /* calculate the current dimensions */
    /* if operating in "dumb" mode, we only need one line */
    lines = smart_terminal ? screen_length - Header_lines : 1;

    if (lines < 0)
	lines = 0;

    /* now, allocate space for the screen buffer */
    screenbuf = calloc(lines, screen_width);
    if (screenbuf == NULL)
    {
	/* oops! */
	return(-1);
    }

    /* return number of lines available */
    /* for dumb terminals, pretend like we can show any amount */
    return(smart_terminal ? lines : Largest);
}