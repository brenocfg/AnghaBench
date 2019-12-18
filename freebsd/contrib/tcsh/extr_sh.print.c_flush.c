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
typedef  int /*<<< orphan*/  ioctl_t ;
typedef  int /*<<< orphan*/  ioclt_t ;

/* Variables and functions */
#define  EBADF 134 
#define  EDQUOT 133 
#define  EIO 132 
#define  ENOENT 131 
#define  ENOTTY 130 
#define  ENXIO 129 
 int /*<<< orphan*/  ERR_SILENT ; 
#define  ESTALE 128 
 scalar_t__ GettingInput ; 
 int LFLUSHO ; 
 int SHDIAG ; 
 int SHOUT ; 
 int /*<<< orphan*/  TIOCLBIC ; 
 int /*<<< orphan*/  TIOCLGET ; 
 int /*<<< orphan*/  Tty_raw_mode ; 
 scalar_t__ didfds ; 
 int errno ; 
 int exitset ; 
 int /*<<< orphan*/  fixerror () ; 
 scalar_t__ haderr ; 
 scalar_t__ handle_interrupt ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* linbuf ; 
 char* linp ; 
 int lmode ; 
 int /*<<< orphan*/  stderror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xexit (int) ; 
 int xwrite (int,char*,int) ; 

void
flush(void)
{
    int unit, oldexitset = exitset;
    static int interrupted = 0;

    /* int lmode; */

    if (linp == linbuf)
	return;
    if (GettingInput && !Tty_raw_mode && linp < &linbuf[sizeof linbuf - 10])
	return;
    if (handle_interrupt)
       exitset = 1;

    if (interrupted) {
	interrupted = 0;
	linp = linbuf;		/* avoid recursion as stderror calls flush */
	if (handle_interrupt)
	    fixerror();
	else
	    stderror(ERR_SILENT);
    }
    interrupted = 1;
    if (haderr)
	unit = didfds ? 2 : SHDIAG;
    else
	unit = didfds ? 1 : SHOUT;
#ifdef COMMENT
#ifdef TIOCLGET
    if (didfds == 0 && ioctl(unit, TIOCLGET, (ioctl_t) & lmode) == 0 &&
	lmode & LFLUSHO) {
	lmode = LFLUSHO;
	(void) ioctl(unit, TIOCLBIC, (ioclt_t) & lmode);
	(void) xwrite(unit, "\n", 1);
    }
#endif
#endif
    if (xwrite(unit, linbuf, linp - linbuf) == -1)
	switch (errno) {
#ifdef EIO
	/* We lost our tty */
	case EIO:
#endif
#ifdef ENXIO
	/*
	 * Deal with Digital Unix 4.0D bogocity, returning ENXIO when
	 * we lose our tty.
	 */
	case ENXIO:
#endif
	/*
	 * IRIX 6.4 bogocity?
	 */
#ifdef ENOTTY
	case ENOTTY:
#endif
#ifdef EBADF
	case EBADF:
#endif
#ifdef ESTALE
	/*
	 * Lost our file descriptor, exit (IRIS4D)
	 */
	case ESTALE:
#endif
#ifdef ENOENT
	/*
	 * Deal with SoFS bogocity: returns ENOENT instead of ESTALE.
	 */
	case ENOENT:
#endif
	/*
	 * Over our quota, writing the history file
	 */
#ifdef EDQUOT
	case EDQUOT:
#endif
	/* Nothing to do, but die */
	    if (handle_interrupt == 0)
		xexit(1);
	    /*FALLTHROUGH*/
	default:
	    if (handle_interrupt)
		fixerror();
	    else
		stderror(ERR_SILENT);
	    break;
	}

    exitset = oldexitset;
    linp = linbuf;
    interrupted = 0;
}