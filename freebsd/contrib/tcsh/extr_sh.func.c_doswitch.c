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
typedef  char Char ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_SYNTAX ; 
 int /*<<< orphan*/  G_ERROR ; 
 char* STRNULL ; 
 int /*<<< orphan*/  TC_SWITCH ; 
 int /*<<< orphan*/  USE (struct command*) ; 
 int /*<<< orphan*/  cleanup_push (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_until (char*) ; 
 char* globone (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  noexec ; 
 int /*<<< orphan*/  search (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfree ; 

void
doswitch(Char **v, struct command *c)
{
    Char *cp, *lp;

    USE(c);
    v++;
    if (!*v || *(*v++) != '(')
	stderror(ERR_SYNTAX);
    cp = **v == ')' ? STRNULL : *v++;
    if (*(*v++) != ')')
	v--;
    if (*v)
	stderror(ERR_SYNTAX);
    lp = globone(cp, G_ERROR);
    cleanup_push(lp, xfree);
    if (!noexec)
	search(TC_SWITCH, 0, lp);
    cleanup_until(lp);
}