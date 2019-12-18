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
struct TYPE_4__ {int /*<<< orphan*/  fd; int /*<<< orphan*/  size; int /*<<< orphan*/ * mmap; } ;
typedef  TYPE_1__ lmo_archive_t ;

/* Variables and functions */
 int /*<<< orphan*/ * MAP_FAILED ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  munmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void lmo_close(lmo_archive_t *ar)
{
	if (ar != NULL)
	{
		if ((ar->mmap != NULL) && (ar->mmap != MAP_FAILED))
			munmap(ar->mmap, ar->size);

		close(ar->fd);
		free(ar);

		ar = NULL;
	}
}