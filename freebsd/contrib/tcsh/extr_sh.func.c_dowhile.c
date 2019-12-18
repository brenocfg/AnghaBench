#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ a_seek; scalar_t__ f_seek; int /*<<< orphan*/  type; } ;
struct whyle {scalar_t__ w_fename; struct whyle* w_next; TYPE_1__ w_end; int /*<<< orphan*/  w_start; } ;
struct command {int dummy; } ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int ERR_EXPRESSION ; 
 int ERR_NAME ; 
 scalar_t__ SEEKEQ (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TCSH_F_SEEK ; 
 int /*<<< orphan*/  TC_WHILE ; 
 int /*<<< orphan*/  USE (struct command*) ; 
 int /*<<< orphan*/  doagain () ; 
 int /*<<< orphan*/  exp0 (int /*<<< orphan*/ ***,int) ; 
 int /*<<< orphan*/  expr (int /*<<< orphan*/ ***) ; 
 scalar_t__ intty ; 
 int /*<<< orphan*/  lineloc ; 
 scalar_t__ noexec ; 
 int /*<<< orphan*/  preread () ; 
 int /*<<< orphan*/  stderror (int) ; 
 int /*<<< orphan*/  toend () ; 
 struct whyle* whyles ; 
 struct whyle* xcalloc (int,int) ; 
 int /*<<< orphan*/  zlast ; 

void
dowhile(Char **v, struct command *c)
{
    int status;
    int again = whyles != 0 && 
			  SEEKEQ(&whyles->w_start, &lineloc) &&
			  whyles->w_fename == 0;

    USE(c);
    v++;
    /*
     * Implement prereading here also, taking care not to evaluate the
     * expression before the loop has been read up from a terminal.
     */
    if (noexec)
	status = 0;
    else if (intty && !again)
	status = !exp0(&v, 1);
    else
	status = !expr(&v);
    if (*v && !noexec)
	stderror(ERR_NAME | ERR_EXPRESSION);
    if (!again) {
	struct whyle *nwp = xcalloc(1, sizeof(*nwp));

	nwp->w_start = lineloc;
	nwp->w_end.type = TCSH_F_SEEK;
	nwp->w_end.f_seek = 0;
	nwp->w_end.a_seek = 0;
	nwp->w_next = whyles;
	whyles = nwp;
	zlast = TC_WHILE;
	if (intty) {
	    /*
	     * The tty preread
	     */
	    preread();
	    doagain();
	    return;
	}
    }
    if (status)
	/* We ain't gonna loop no more, no more! */
	toend();
}