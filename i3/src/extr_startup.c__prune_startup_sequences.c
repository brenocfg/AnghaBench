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
typedef  scalar_t__ time_t ;
struct Startup_Sequence {scalar_t__ delete_at; } ;

/* Variables and functions */
 struct Startup_Sequence* TAILQ_END (int /*<<< orphan*/ *) ; 
 struct Startup_Sequence* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct Startup_Sequence* TAILQ_NEXT (struct Startup_Sequence*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sequences ; 
 int /*<<< orphan*/  startup_sequence_delete (struct Startup_Sequence*) ; 
 int /*<<< orphan*/  startup_sequences ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int _prune_startup_sequences(void) {
    time_t current_time = time(NULL);
    int active_sequences = 0;

    /* Traverse the list and delete everything which was marked for deletion 30
     * seconds ago or earlier. */
    struct Startup_Sequence *current, *next;
    for (next = TAILQ_FIRST(&startup_sequences);
         next != TAILQ_END(&startup_sequences);) {
        current = next;
        next = TAILQ_NEXT(next, sequences);

        if (current->delete_at == 0) {
            active_sequences++;
            continue;
        }

        if (current_time <= current->delete_at)
            continue;

        startup_sequence_delete(current);
    }

    return active_sequences;
}