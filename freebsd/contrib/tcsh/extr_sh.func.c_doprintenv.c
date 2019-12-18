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
struct command {int dummy; } ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int /*<<< orphan*/  STR1 ; 
 int /*<<< orphan*/ ** STR_environ ; 
 int /*<<< orphan*/  STRstatus ; 
 int /*<<< orphan*/  USE (struct command*) ; 
 int /*<<< orphan*/  VAR_READWRITE ; 
 int /*<<< orphan*/  cleanup_push (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_until (int*) ; 
 int output_raw ; 
 int /*<<< orphan*/  output_raw_restore ; 
 int /*<<< orphan*/  pintr_push_enable (int*) ; 
 int /*<<< orphan*/  setcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ setintr ; 
 int /*<<< orphan*/ * tgetenv (int /*<<< orphan*/ *) ; 
 int xlate_cr ; 
 int /*<<< orphan*/  xlate_cr_cleanup ; 
 int /*<<< orphan*/  xprintf (char*,int /*<<< orphan*/ *) ; 

void
doprintenv(Char **v, struct command *c) 
{
    Char   *e;

    USE(c);
    v++;
    if (*v == 0) {
	Char **ep;

	xlate_cr = 1;
	cleanup_push(&xlate_cr, xlate_cr_cleanup);
	for (ep = STR_environ; *ep; ep++) {
	    if (setintr) {
		int old_pintr_disabled;

		pintr_push_enable(&old_pintr_disabled);
		cleanup_until(&old_pintr_disabled);
	    }
	    xprintf("%S\n", *ep);
	}
	cleanup_until(&xlate_cr);
    }
    else if ((e = tgetenv(*v)) != NULL) {
	int old_output_raw;

	old_output_raw = output_raw;
	output_raw = 1;
	cleanup_push(&old_output_raw, output_raw_restore);
	xprintf("%S\n", e);
	cleanup_until(&old_output_raw);
    }
    else
	setcopy(STRstatus, STR1, VAR_READWRITE);
}