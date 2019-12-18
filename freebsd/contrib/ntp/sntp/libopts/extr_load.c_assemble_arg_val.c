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
typedef  scalar_t__ tOptionLoadMode ;

/* Variables and functions */
 int /*<<< orphan*/  ARG_BREAK_STR ; 
 int IS_WHITESPACE_CHAR (char) ; 
 void* NUL ; 
 scalar_t__ OPTION_LOAD_KEEP ; 
 char* SPN_WHITESPACE_CHARS (char*) ; 
 int strlen (char*) ; 
 char* strpbrk (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
assemble_arg_val(char * txt, tOptionLoadMode mode)
{
    char * end = strpbrk(txt, ARG_BREAK_STR);
    int    space_break;

    /*
     *  Not having an argument to a configurable name is okay.
     */
    if (end == NULL)
        return txt + strlen(txt);

    /*
     *  If we are keeping all whitespace, then the  modevalue starts with the
     *  character that follows the end of the configurable name, regardless
     *  of which character caused it.
     */
    if (mode == OPTION_LOAD_KEEP) {
        *(end++) = NUL;
        return end;
    }

    /*
     *  If the name ended on a white space character, remember that
     *  because we'll have to skip over an immediately following ':' or '='
     *  (and the white space following *that*).
     */
    space_break = IS_WHITESPACE_CHAR(*end);
    *(end++) = NUL;

    end = SPN_WHITESPACE_CHARS(end);
    if (space_break && ((*end == ':') || (*end == '=')))
        end = SPN_WHITESPACE_CHARS(end+1);

    return end;
}