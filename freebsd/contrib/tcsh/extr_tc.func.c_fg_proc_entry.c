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
struct process {int /*<<< orphan*/  p_command; scalar_t__ p_procid; } ;
typedef  int /*<<< orphan*/  jmp_buf_t ;
typedef  scalar_t__ Char ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_BADJOB ; 
 scalar_t__ GettingInput ; 
 int /*<<< orphan*/  alarm (int /*<<< orphan*/ ) ; 
 int alrmcatch_disabled ; 
 int /*<<< orphan*/  cleanup_pop_mark (size_t) ; 
 size_t cleanup_push_mark () ; 
 int /*<<< orphan*/  disabled_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  getexit (int /*<<< orphan*/ ) ; 
 int haderr ; 
 int /*<<< orphan*/  pendjob () ; 
 int /*<<< orphan*/  pintr_disabled ; 
 int /*<<< orphan*/  pjwait (struct process*) ; 
 int /*<<< orphan*/  pstart (struct process*,int) ; 
 int /*<<< orphan*/  resexit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setalarm (int) ; 
 scalar_t__ setexit () ; 
 int /*<<< orphan*/  stderror (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

void
fg_proc_entry(struct process *pp)
{
    jmp_buf_t osetexit;
    int    ohaderr;
    Char    oGettingInput;
    size_t omark;

    getexit(osetexit);

    pintr_disabled++;
    oGettingInput = GettingInput;
    GettingInput = 0;

    ohaderr = haderr;		/* we need to ignore setting of haderr due to
				 * process getting stopped by a signal */
    omark = cleanup_push_mark();
    if (setexit() == 0) {	/* come back here after pjwait */
	pendjob();
	(void) alarm(0);	/* No autologout */
	alrmcatch_disabled = 1;
	if (!pstart(pp, 1)) {
	    pp->p_procid = 0;
	    stderror(ERR_BADJOB, pp->p_command, strerror(errno));
	}
	pjwait(pp);
    }
    setalarm(1);		/* Autologout back on */
    cleanup_pop_mark(omark);
    resexit(osetexit);
    haderr = ohaderr;
    GettingInput = oGettingInput;

    disabled_cleanup(&pintr_disabled);
}