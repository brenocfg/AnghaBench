#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* next; int /*<<< orphan*/ * obj; } ;
typedef  int /*<<< orphan*/  RtldLockState ;
typedef  TYPE_1__ Needed_Entry ;

/* Variables and functions */
 int /*<<< orphan*/  dlclose_locked (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void
free_needed_filtees(Needed_Entry *n, RtldLockState *lockstate)
{
    Needed_Entry *needed, *needed1;

    for (needed = n; needed != NULL; needed = needed->next) {
	if (needed->obj != NULL) {
	    dlclose_locked(needed->obj, lockstate);
	    needed->obj = NULL;
	}
    }
    for (needed = n; needed != NULL; needed = needed1) {
	needed1 = needed->next;
	free(needed);
    }
}