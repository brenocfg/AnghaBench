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
struct command {int dummy; } ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int ERR_BADJOB ; 
 int ERR_NAME ; 
 int /*<<< orphan*/  USE (struct command*) ; 
 int /*<<< orphan*/  errno ; 
 struct process* pfind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pstart (struct process*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderror (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

void
dobg1(Char **v, struct command *c)
{
    struct process *pp;

    USE(c);
    pp = pfind(v[0]);
    if (!pstart(pp, 0)) {
	pp->p_procid = 0;
	stderror(ERR_NAME|ERR_BADJOB, pp->p_command, strerror(errno));
    }
}