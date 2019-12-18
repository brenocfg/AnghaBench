#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* posix_spawn_file_actions_t ;
struct TYPE_7__ {int fae_fildes; int /*<<< orphan*/  fae_action; } ;
typedef  TYPE_2__ posix_spawn_file_actions_entry_t ;
struct TYPE_6__ {int /*<<< orphan*/  fa_list; } ;

/* Variables and functions */
 int EBADF ; 
 int /*<<< orphan*/  FAE_CLOSE ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int errno ; 
 int /*<<< orphan*/  fae_list ; 
 TYPE_2__* malloc (int) ; 

int
posix_spawn_file_actions_addclose(posix_spawn_file_actions_t *fa,
    int fildes)
{
	posix_spawn_file_actions_entry_t *fae;

	if (fildes < 0)
		return (EBADF);

	/* Allocate object */
	fae = malloc(sizeof(posix_spawn_file_actions_entry_t));
	if (fae == NULL)
		return (errno);

	/* Set values and store in queue */
	fae->fae_action = FAE_CLOSE;
	fae->fae_fildes = fildes;

	STAILQ_INSERT_TAIL(&(*fa)->fa_list, fae, fae_list);
	return (0);
}