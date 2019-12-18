#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int use_env; int use_tioctl; } ;
struct TYPE_8__ {int _use_env; int _use_tioctl; scalar_t__ _filtered; } ;
struct TYPE_7__ {int /*<<< orphan*/  Filedes; } ;
struct TYPE_6__ {TYPE_3__* csp; } ;
typedef  TYPE_1__ TERMINAL_CONTROL_BLOCK ;
typedef  TYPE_2__ TERMINAL ;
typedef  int /*<<< orphan*/  STRUCT_WINSIZE ;
typedef  TYPE_3__ SCREEN ;

/* Variables and functions */
 int /*<<< orphan*/  AssertTCB () ; 
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  IOCTL_WINSIZE ; 
 int OK ; 
 int /*<<< orphan*/  T (char*) ; 
 int TRUE ; 
 int WINSIZE_COLS (int /*<<< orphan*/ ) ; 
 int WINSIZE_ROWS (int /*<<< orphan*/ ) ; 
 int _nc_getenv_num (char*) ; 
 TYPE_5__ _nc_prescreen ; 
 int /*<<< orphan*/  _nc_setenv_num (char*,int) ; 
 int /*<<< orphan*/  _scrsize (int*) ; 
 short columns ; 
 scalar_t__ errno ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ isatty (int /*<<< orphan*/ ) ; 
 short lines ; 

__attribute__((used)) static int
drv_size(TERMINAL_CONTROL_BLOCK * TCB, int *linep, int *colp)
{
    SCREEN *sp;
    bool useEnv = TRUE;
    bool useTioctl = TRUE;

    AssertTCB();
    sp = TCB->csp;		/* can be null here */

    if (sp) {
	useEnv = sp->_use_env;
	useTioctl = sp->_use_tioctl;
    } else {
	useEnv = _nc_prescreen.use_env;
	useTioctl = _nc_prescreen.use_tioctl;
    }

    /* figure out the size of the screen */
    T(("screen size: terminfo lines = %d columns = %d", lines, columns));

    *linep = (int) lines;
    *colp = (int) columns;

    if (useEnv || useTioctl) {
	int value;

#ifdef __EMX__
	{
	    int screendata[2];
	    _scrsize(screendata);
	    *colp = screendata[0];
	    *linep = ((sp != 0 && sp->_filtered)
		      ? 1
		      : screendata[1]);
	    T(("EMX screen size: environment LINES = %d COLUMNS = %d",
	       *linep, *colp));
	}
#endif
#if HAVE_SIZECHANGE
	/* try asking the OS */
	{
	    TERMINAL *termp = (TERMINAL *) TCB;
	    if (isatty(termp->Filedes)) {
		STRUCT_WINSIZE size;

		errno = 0;
		do {
		    if (ioctl(termp->Filedes, IOCTL_WINSIZE, &size) >= 0) {
			*linep = ((sp != 0 && sp->_filtered)
				  ? 1
				  : WINSIZE_ROWS(size));
			*colp = WINSIZE_COLS(size);
			T(("SYS screen size: environment LINES = %d COLUMNS = %d",
			   *linep, *colp));
			break;
		    }
		} while
		    (errno == EINTR);
	    }
	}
#endif /* HAVE_SIZECHANGE */

	if (useEnv) {
	    if (useTioctl) {
		/*
		 * If environment variables are used, update them.
		 */
		if ((sp == 0 || !sp->_filtered) && _nc_getenv_num("LINES") > 0) {
		    _nc_setenv_num("LINES", *linep);
		}
		if (_nc_getenv_num("COLUMNS") > 0) {
		    _nc_setenv_num("COLUMNS", *colp);
		}
	    }

	    /*
	     * Finally, look for environment variables.
	     *
	     * Solaris lets users override either dimension with an environment
	     * variable.
	     */
	    if ((value = _nc_getenv_num("LINES")) > 0) {
		*linep = value;
		T(("screen size: environment LINES = %d", *linep));
	    }
	    if ((value = _nc_getenv_num("COLUMNS")) > 0) {
		*colp = value;
		T(("screen size: environment COLUMNS = %d", *colp));
	    }
	}

	/* if we can't get dynamic info about the size, use static */
	if (*linep <= 0) {
	    *linep = (int) lines;
	}
	if (*colp <= 0) {
	    *colp = (int) columns;
	}

	/* the ultimate fallback, assume fixed 24x80 size */
	if (*linep <= 0) {
	    *linep = 24;
	}
	if (*colp <= 0) {
	    *colp = 80;
	}

	/*
	 * Put the derived values back in the screen-size caps, so
	 * tigetnum() and tgetnum() will do the right thing.
	 */
	lines = (short) (*linep);
	columns = (short) (*colp);
    }

    T(("screen size is %dx%d", *linep, *colp));
    return OK;
}