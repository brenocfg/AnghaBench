#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* posix_spawn_file_actions_t ;
struct TYPE_8__ {int fae_fildes; int fae_oflag; int /*<<< orphan*/  fae_mode; int /*<<< orphan*/ * fae_path; int /*<<< orphan*/  fae_action; } ;
typedef  TYPE_2__ posix_spawn_file_actions_entry_t ;
typedef  int /*<<< orphan*/  mode_t ;
struct TYPE_7__ {int /*<<< orphan*/  fa_list; } ;

/* Variables and functions */
 int EBADF ; 
 int /*<<< orphan*/  FAE_OPEN ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int errno ; 
 int /*<<< orphan*/  fae_list ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 TYPE_2__* malloc (int) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 

int
posix_spawn_file_actions_addopen(posix_spawn_file_actions_t * __restrict fa,
    int fildes, const char * __restrict path, int oflag, mode_t mode)
{
	posix_spawn_file_actions_entry_t *fae;
	int error;

	if (fildes < 0)
		return (EBADF);

	/* Allocate object */
	fae = malloc(sizeof(posix_spawn_file_actions_entry_t));
	if (fae == NULL)
		return (errno);

	/* Set values and store in queue */
	fae->fae_action = FAE_OPEN;
	fae->fae_path = strdup(path);
	if (fae->fae_path == NULL) {
		error = errno;
		free(fae);
		return (error);
	}
	fae->fae_fildes = fildes;
	fae->fae_oflag = oflag;
	fae->fae_mode = mode;

	STAILQ_INSERT_TAIL(&(*fa)->fa_list, fae, fae_list);
	return (0);
}