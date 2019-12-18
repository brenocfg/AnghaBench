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
typedef  int /*<<< orphan*/ * command ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int ERR_NAME ; 
 int ERR_TERMINAL ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  USE (int /*<<< orphan*/ **) ; 
 scalar_t__ intty ; 
 scalar_t__ setintr ; 
 int /*<<< orphan*/  sigset_interrupting (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderror (int) ; 

void
dohup(Char **v, struct command *c)
{
    USE(c);
    USE(v);
    if (intty)
	stderror(ERR_NAME | ERR_TERMINAL);
    if (setintr == 0)
    	sigset_interrupting(SIGHUP, SIG_DFL);
}