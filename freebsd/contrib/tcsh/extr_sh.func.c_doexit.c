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
 int ERR_EXPRESSION ; 
 int ERR_NAME ; 
 int /*<<< orphan*/  SHIN ; 
 int /*<<< orphan*/  STRstatus ; 
 int /*<<< orphan*/  USE (struct command*) ; 
 int /*<<< orphan*/  VAR_READWRITE ; 
 int /*<<< orphan*/  btoeof () ; 
 scalar_t__ chkstop ; 
 scalar_t__ evalvec ; 
 int /*<<< orphan*/  expr (int /*<<< orphan*/ ***) ; 
 scalar_t__ intact ; 
 scalar_t__ intty ; 
 int /*<<< orphan*/  panystop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderror (int) ; 
 int /*<<< orphan*/  xclose (int /*<<< orphan*/ ) ; 

void
doexit(Char **v, struct command *c)
{
    USE(c);

    if (chkstop == 0 && (intty || intact) && evalvec == 0)
	panystop(0);
    /*
     * Don't DEMAND parentheses here either.
     */
    v++;
    if (*v) {
	setv(STRstatus, putn(expr(&v)), VAR_READWRITE);
	if (*v)
	    stderror(ERR_NAME | ERR_EXPRESSION);
    }
    btoeof();
#if 0
    if (intty)
#endif
    /* Always close, why only on ttys? */
	xclose(SHIN);
}