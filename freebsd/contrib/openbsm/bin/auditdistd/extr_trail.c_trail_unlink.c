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
struct trail {scalar_t__ tr_magic; int /*<<< orphan*/  tr_dirname; int /*<<< orphan*/  tr_dirfp; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 scalar_t__ TRAIL_MAGIC ; 
 int dirfd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pjdlog_debug (int,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  pjdlog_errno (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*) ; 
 int unlinkat (int,char const*,int /*<<< orphan*/ ) ; 

void
trail_unlink(struct trail *trail, const char *filename)
{
	int dfd;

	PJDLOG_ASSERT(trail->tr_magic == TRAIL_MAGIC);
	PJDLOG_ASSERT(filename != NULL);
	PJDLOG_ASSERT(filename[0] != '\0');

	dfd = dirfd(trail->tr_dirfp);
	PJDLOG_ASSERT(dfd >= 0);

	if (unlinkat(dfd, filename, 0) == -1) {
		pjdlog_errno(LOG_ERR, "Unable to remove \"%s/%s\"",
		    trail->tr_dirname, filename);
	} else {
		pjdlog_debug(1, "Trail file \"%s/%s\" removed.",
		    trail->tr_dirname, filename);
	}
}