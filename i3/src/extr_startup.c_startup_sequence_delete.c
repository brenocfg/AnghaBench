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
struct Startup_Sequence {int /*<<< orphan*/  workspace; int /*<<< orphan*/  id; int /*<<< orphan*/  context; scalar_t__ delete_at; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*,int /*<<< orphan*/ ,long long,long long) ; 
 int /*<<< orphan*/  FREE (struct Startup_Sequence*) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct Startup_Sequence*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sequences ; 
 int /*<<< orphan*/  sn_launcher_context_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  startup_sequences ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

void startup_sequence_delete(struct Startup_Sequence *sequence) {
    assert(sequence != NULL);
    DLOG("Deleting startup sequence %s, delete_at = %lld, current_time = %lld\n",
         sequence->id, (long long)sequence->delete_at, (long long)time(NULL));

    /* Unref the context, will be free()d */
    sn_launcher_context_unref(sequence->context);

    /* Delete our internal sequence */
    TAILQ_REMOVE(&startup_sequences, sequence, sequences);

    free(sequence->id);
    free(sequence->workspace);
    FREE(sequence);
}