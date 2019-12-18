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
 char* Cursor ; 
 char* InputBuf ; 
 char* LastChar ; 
 int /*<<< orphan*/  MISMATCH (char) ; 
 int /*<<< orphan*/  SPELL ; 
 scalar_t__ find_cmd (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ iscmdmeta (char) ; 
 scalar_t__ ismetahash (char) ; 
 scalar_t__ starting_a_command (char*,char*) ; 
 int tenematch (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
SpellLine(int cmdonly)
{
    int     endflag, matchval;
    Char   *argptr, *OldCursor, *OldLastChar;

    OldLastChar = LastChar;
    OldCursor = Cursor;
    argptr = InputBuf;
    endflag = 1;
    matchval = 0;
    do {
	while (ismetahash(*argptr) || iscmdmeta(*argptr))
	    argptr++;
	for (Cursor = argptr;
	     *Cursor != '\0' && ((Cursor != argptr && Cursor[-1] == '\\') ||
				 (!ismetahash(*Cursor) && !iscmdmeta(*Cursor)));
	     Cursor++)
	     continue;
	if (*Cursor == '\0') {
	    Cursor = LastChar;
	    if (LastChar[-1] == '\n')
		Cursor--;
	    endflag = 0;
	}
	if (!MISMATCH(*argptr) &&
	    (!cmdonly || starting_a_command(argptr, InputBuf))) {
#ifdef WINNT_NATIVE
	    /*
	     * This hack avoids correcting drive letter changes
	     */
	    if((Cursor - InputBuf) != 2 || (char)InputBuf[1] != ':')
#endif /* WINNT_NATIVE */
	    {
#ifdef HASH_SPELL_CHECK
		Char save;
		size_t len = Cursor - InputBuf;

		save = InputBuf[len];
		InputBuf[len] = '\0';
		if (find_cmd(InputBuf, 0) != 0) {
		    InputBuf[len] = save;
		    argptr = Cursor;
		    continue;
		}
		InputBuf[len] = save;
#endif /* HASH_SPELL_CHECK */
		switch (tenematch(InputBuf, Cursor - InputBuf, SPELL)) {
		case 1:		/* corrected */
		    matchval = 1;
		    break;
		case -1:		/* couldn't be corrected */
		    if (!matchval)
			matchval = -1;
		    break;
		default:		/* was correct */
		    break;
		}
	    }
	    if (LastChar != OldLastChar) {
		if (argptr < OldCursor)
		    OldCursor += (LastChar - OldLastChar);
		OldLastChar = LastChar;
	    }
	}
	argptr = Cursor;
    } while (endflag);
    Cursor = OldCursor;
    return matchval;
}