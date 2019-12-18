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

/* Variables and functions */
 int /*<<< orphan*/  ERR_PIPE ; 
 int /*<<< orphan*/  close_on_exec (int,int) ; 
 int dmove (int,int) ; 
 scalar_t__ pipe (int*) ; 
 int /*<<< orphan*/  stderror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xclose (int) ; 

void
mypipe(int *pv)
{

    if (pipe(pv) < 0)
	goto oops;
    (void)close_on_exec(pv[0] = dmove(pv[0], -1), 1);
    (void)close_on_exec(pv[1] = dmove(pv[1], -1), 1);
    if (pv[0] >= 0 && pv[1] >= 0)
	return;
    if (pv[0] >= 0)
	xclose(pv[0]);
    if (pv[1] >= 0)
	xclose(pv[1]);
oops:
    stderror(ERR_PIPE);
}