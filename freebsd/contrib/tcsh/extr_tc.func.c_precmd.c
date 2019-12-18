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
 int /*<<< orphan*/  CGETS (int,int,char*) ; 
 int /*<<< orphan*/ * STRprecmd ; 
 int /*<<< orphan*/ * STRunalias ; 
 scalar_t__ adrof1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aliases ; 
 int /*<<< orphan*/  aliasrun (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cleanup_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_until (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disabled_cleanup ; 
 int /*<<< orphan*/  pintr_disabled ; 
 int precmd_active ; 
 int /*<<< orphan*/  whyles ; 
 int /*<<< orphan*/  xprintf (char*,int /*<<< orphan*/ ) ; 

void
precmd(void)
{
    pintr_disabled++;
    cleanup_push(&pintr_disabled, disabled_cleanup);
    if (precmd_active) {	/* an error must have been caught */
	aliasrun(2, STRunalias, STRprecmd);
	xprintf("%s", CGETS(22, 3, "Faulty alias 'precmd' removed.\n"));
	goto leave;
    }
    precmd_active = 1;
    if (!whyles && adrof1(STRprecmd, &aliases))
	aliasrun(1, STRprecmd, NULL);
leave:
    precmd_active = 0;
    cleanup_until(&pintr_disabled);
}