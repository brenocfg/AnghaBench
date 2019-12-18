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
 int /*<<< orphan*/  STRstatus ; 
 int TRUE ; 
 int /*<<< orphan*/  USE (struct command*) ; 
 int /*<<< orphan*/  VAR_READWRITE ; 
 int cmd_expand (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
dowhich(Char **v, struct command *c)
{
    int rv = TRUE;
    USE(c);

    /*
     * We don't want to glob dowhich args because we lose quoteing
     * E.g. which \ls if ls is aliased will not work correctly if
     * we glob here.
     */

    while (*++v) 
	rv &= cmd_expand(*v, NULL);

    if (!rv)
	setcopy(STRstatus, STR1, VAR_READWRITE);
}