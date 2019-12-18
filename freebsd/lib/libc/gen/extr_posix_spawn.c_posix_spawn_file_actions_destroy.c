#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* posix_spawn_file_actions_t ;
struct TYPE_6__ {scalar_t__ fae_action; struct TYPE_6__* fae_path; int /*<<< orphan*/  fa_list; } ;
typedef  TYPE_1__ posix_spawn_file_actions_entry_t ;

/* Variables and functions */
 scalar_t__ FAE_OPEN ; 
 TYPE_1__* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fae_list ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

int
posix_spawn_file_actions_destroy(posix_spawn_file_actions_t *fa)
{
	posix_spawn_file_actions_entry_t *fae;

	while ((fae = STAILQ_FIRST(&(*fa)->fa_list)) != NULL) {
		/* Remove file action entry from the queue */
		STAILQ_REMOVE_HEAD(&(*fa)->fa_list, fae_list);

		/* Deallocate file action entry */
		if (fae->fae_action == FAE_OPEN)
			free(fae->fae_path);
		free(fae);
	}

	free(*fa);
	return (0);
}