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
struct trail {scalar_t__ tr_magic; int tr_filefd; int /*<<< orphan*/  tr_dirfp; } ;

/* Variables and functions */
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 scalar_t__ TRAIL_MAGIC ; 
 int /*<<< orphan*/  bzero (struct trail*,int) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct trail*) ; 
 int /*<<< orphan*/  trail_close (struct trail*) ; 

void
trail_free(struct trail *trail)
{

	PJDLOG_ASSERT(trail->tr_magic == TRAIL_MAGIC);

	if (trail->tr_filefd != -1)
		trail_close(trail);
	closedir(trail->tr_dirfp);
	bzero(trail, sizeof(*trail));
	trail->tr_magic = 0;
	trail->tr_filefd = -1;
	free(trail);
}