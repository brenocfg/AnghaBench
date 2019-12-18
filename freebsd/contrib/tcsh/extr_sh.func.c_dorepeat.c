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
 int /*<<< orphan*/  STRrepeat ; 
 scalar_t__ Strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_push (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_until (int*) ; 
 int /*<<< orphan*/  disabled_cleanup ; 
 int /*<<< orphan*/  donefds () ; 
 int getn (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lshift (int /*<<< orphan*/ **,int) ; 
 scalar_t__ noexec ; 
 int pintr_disabled ; 
 int /*<<< orphan*/  reexecute (struct command*) ; 
 scalar_t__ setintr ; 

void
dorepeat(Char **v, struct command *kp)
{
    int i = 1;

    do {
	i *= getn(v[1]);
	lshift(v, 2);
    } while (v[0] != NULL && Strcmp(v[0], STRrepeat) == 0);
    if (noexec)
	i = 1;

    if (setintr) {
	pintr_disabled++;
	cleanup_push(&pintr_disabled, disabled_cleanup);
    }
    while (i > 0) {
	if (setintr && pintr_disabled == 1) {
	    cleanup_until(&pintr_disabled);
	    pintr_disabled++;
	    cleanup_push(&pintr_disabled, disabled_cleanup);
	}
	reexecute(kp);
	--i;
    }
    if (setintr && pintr_disabled == 1)
        cleanup_until(&pintr_disabled);
    donefds();
}