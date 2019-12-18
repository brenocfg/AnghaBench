#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  term_names; } ;
struct TYPE_10__ {TYPE_1__ type; } ;
struct TYPE_9__ {int /*<<< orphan*/  magic; int /*<<< orphan*/ * csp; } ;
typedef  TYPE_1__ TERMTYPE ;
typedef  TYPE_2__ TERMINAL_CONTROL_BLOCK ;
typedef  TYPE_3__ TERMINAL ;
typedef  int /*<<< orphan*/  SCREEN ;
typedef  int /*<<< orphan*/  NCURSES_SP_NAME ;
typedef  int /*<<< orphan*/  NCURSES_SP_ARGx ;

/* Variables and functions */
 int FALSE ; 
 int NAMESIZE ; 
 int /*<<< orphan*/  TCBMAGIC ; 
 int TGETENT_ERR ; 
 int TGETENT_NO ; 
 int TGETENT_YES ; 
 int TRUE ; 
 scalar_t__ VALID_STRING (int /*<<< orphan*/ ) ; 
 TYPE_1__* _nc_fallback (char const*) ; 
 int _nc_setup_tinfo (char const*,TYPE_1__*) ; 
 int /*<<< orphan*/  _nc_tinfo_cmdch (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  clear_screen ; 
 int /*<<< orphan*/ * command_character ; 
 int /*<<< orphan*/  cursor_address ; 
 int /*<<< orphan*/  cursor_down ; 
 int /*<<< orphan*/  cursor_home ; 
 scalar_t__ generic_type ; 
 scalar_t__ hard_copy ; 
 int /*<<< orphan*/  ret_error0 (int,char*) ; 
 int /*<<< orphan*/  ret_error1 (int,char*,char const*) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,size_t) ; 
 char* ttytype ; 

__attribute__((used)) static bool
drv_CanHandle(TERMINAL_CONTROL_BLOCK * TCB, const char *tname, int *errret)
{
    bool result = FALSE;
    int status;
    TERMINAL *termp;
    SCREEN *sp;

    assert(TCB != 0 && tname != 0);
    termp = (TERMINAL *) TCB;
    sp = TCB->csp;
    TCB->magic = TCBMAGIC;

#if (NCURSES_USE_DATABASE || NCURSES_USE_TERMCAP)
    status = _nc_setup_tinfo(tname, &termp->type);
#else
    status = TGETENT_NO;
#endif

    /* try fallback list if entry on disk */
    if (status != TGETENT_YES) {
	const TERMTYPE *fallback = _nc_fallback(tname);

	if (fallback) {
	    termp->type = *fallback;
	    status = TGETENT_YES;
	}
    }

    if (status != TGETENT_YES) {
	NCURSES_SP_NAME(del_curterm) (NCURSES_SP_ARGx termp);
	if (status == TGETENT_ERR) {
	    ret_error0(status, "terminals database is inaccessible\n");
	} else if (status == TGETENT_NO) {
	    ret_error1(status, "unknown terminal type.\n", tname);
	}
    }
    result = TRUE;
#if !USE_REENTRANT
    strncpy(ttytype, termp->type.term_names, (size_t) NAMESIZE - 1);
    ttytype[NAMESIZE - 1] = '\0';
#endif

    if (command_character)
	_nc_tinfo_cmdch(termp, *command_character);

    if (generic_type) {
	/*
	 * BSD 4.3's termcap contains mis-typed "gn" for wy99.  Do a sanity
	 * check before giving up.
	 */
	if ((VALID_STRING(cursor_address)
	     || (VALID_STRING(cursor_down) && VALID_STRING(cursor_home)))
	    && VALID_STRING(clear_screen)) {
	    ret_error1(TGETENT_YES, "terminal is not really generic.\n", tname);
	} else {
	    ret_error1(TGETENT_NO, "I need something more specific.\n", tname);
	}
    }
    if (hard_copy) {
	ret_error1(TGETENT_YES, "I can't handle hardcopy terminals.\n", tname);
    }

    return result;
}