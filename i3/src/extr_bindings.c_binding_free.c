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
struct Binding_Keycode {struct Binding_Keycode* command; struct Binding_Keycode* symbol; int /*<<< orphan*/  keycodes_head; } ;
typedef  struct Binding_Keycode Binding ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (struct Binding_Keycode*) ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct Binding_Keycode* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct Binding_Keycode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  keycodes ; 

void binding_free(Binding *bind) {
    if (bind == NULL) {
        return;
    }

    while (!TAILQ_EMPTY(&(bind->keycodes_head))) {
        struct Binding_Keycode *first = TAILQ_FIRST(&(bind->keycodes_head));
        TAILQ_REMOVE(&(bind->keycodes_head), first, keycodes);
        FREE(first);
    }

    FREE(bind->symbol);
    FREE(bind->command);
    FREE(bind);
}