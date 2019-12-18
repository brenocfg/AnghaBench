#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int c_oflag; } ;

/* Variables and functions */
 int OCRNL ; 
 int ONLCR ; 
 int ONLRET ; 
 char PC ; 
 int /*<<< orphan*/  SET_TTY (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  STDERR_FILENO ; 
 int TAB3 ; 
 int TRUE ; 
 int /*<<< orphan*/  cat (char*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 char* init_file ; 
 scalar_t__ isreset ; 
 int /*<<< orphan*/  napms (int) ; 
 TYPE_1__ oldmode ; 
 int /*<<< orphan*/  outc ; 
 char* pad_char ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ ) ; 
 char* reset_1string ; 
 char* reset_2string ; 
 char* reset_file ; 
 int set_tabs () ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  tputs (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_init(void)
{
    char *p;
    bool settle;

#ifdef __OBSOLETE__
    if (pad_char != (char *) 0)	/* Get/set pad character. */
	PC = pad_char[0];
#endif /* OBSOLETE */

#ifdef TAB3
    if (oldmode.c_oflag & (TAB3 | ONLCR | OCRNL | ONLRET)) {
	oldmode.c_oflag &= (TAB3 | ONLCR | OCRNL | ONLRET);
	SET_TTY(STDERR_FILENO, &oldmode);
    }
#endif
    settle = set_tabs();

    if (isreset) {
	if ((p = reset_1string) != 0) {
	    tputs(p, 0, outc);
	    settle = TRUE;
	}
	if ((p = reset_2string) != 0) {
	    tputs(p, 0, outc);
	    settle = TRUE;
	}
	/* What about rf, rs3, as per terminfo man page? */
	/* also might be nice to send rmacs, rmul, rmm */
	if ((p = reset_file) != 0
	    || (p = init_file) != 0) {
	    cat(p);
	    settle = TRUE;
	}
    }

    if (settle) {
	(void) putc('\r', stderr);
	(void) fflush(stderr);
	(void) napms(1000);	/* Settle the terminal. */
    }
}