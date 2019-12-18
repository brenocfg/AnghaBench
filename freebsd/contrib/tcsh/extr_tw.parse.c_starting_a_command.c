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
typedef  char Char ;

/* Variables and functions */
 int EVEN (int) ; 
 int FALSE ; 
 char* Strchr (char*,char) ; 
 int TRUE ; 
 int /*<<< orphan*/  iscmdmeta (char) ; 

int
starting_a_command(Char *wordstart, Char *inputline)
{
    Char *ptr, *ncmdstart;
    int     count, bsl;
    static  Char
            cmdstart[] = {'`', ';', '&', '(', '|', '\0'},
            cmdalive[] = {' ', '\t', '\'', '"', '<', '>', '\0'};

    /*
     * Find if the number of backquotes is odd or even.
     */
    for (ptr = wordstart, count = 0;
	 ptr >= inputline;
	 count += (*ptr-- == '`'))
	continue;
    /*
     * if the number of backquotes is even don't include the backquote char in
     * the list of command starting delimiters [if it is zero, then it does not
     * matter]
     */
    ncmdstart = cmdstart + EVEN(count);

    /*
     * look for the characters previous to this word if we find a command
     * starting delimiter we break. if we find whitespace and another previous
     * word then we are not a command
     * 
     * count is our state machine: 0 looking for anything 1 found white-space
     * looking for non-ws
     */
    for (count = 0; wordstart >= inputline; wordstart--) {
	if (*wordstart == '\0')
	    continue;
	if (Strchr(ncmdstart, *wordstart)) {
	    for (ptr = wordstart, bsl = 0; *(--ptr) == '\\'; bsl++);
	    if (bsl & 1) {
		wordstart--;
		continue;
	    } else
		break;
	}
	/*
	 * found white space
	 */
	if ((ptr = Strchr(cmdalive, *wordstart)) != NULL)
	    count = 1;
	if (count == 1 && !ptr)
	    return (FALSE);
    }

    if (wordstart > inputline)
	switch (*wordstart) {
	case '&':		/* Look for >& */
	    while (wordstart > inputline &&
		   (*--wordstart == ' ' || *wordstart == '\t'))
		continue;
	    if (*wordstart == '>')
		return (FALSE);
	    break;
	case '(':		/* check for foreach, if etc. */
	    while (wordstart > inputline &&
		   (*--wordstart == ' ' || *wordstart == '\t'))
		continue;
	    if (!iscmdmeta(*wordstart) &&
		(*wordstart != ' ' && *wordstart != '\t'))
		return (FALSE);
	    break;
	default:
	    break;
	}
    return (TRUE);
}