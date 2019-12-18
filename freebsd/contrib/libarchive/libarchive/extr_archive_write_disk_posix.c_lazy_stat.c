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
struct archive_write_disk {scalar_t__ fd; int /*<<< orphan*/  archive; int /*<<< orphan*/  st; int /*<<< orphan*/ * pst; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int ARCHIVE_WARN ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ fstat (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ lstat (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
lazy_stat(struct archive_write_disk *a)
{
	if (a->pst != NULL) {
		/* Already have stat() data available. */
		return (ARCHIVE_OK);
	}
#ifdef HAVE_FSTAT
	if (a->fd >= 0 && fstat(a->fd, &a->st) == 0) {
		a->pst = &a->st;
		return (ARCHIVE_OK);
	}
#endif
	/*
	 * XXX At this point, symlinks should not be hit, otherwise
	 * XXX a race occurred.  Do we want to check explicitly for that?
	 */
	if (lstat(a->name, &a->st) == 0) {
		a->pst = &a->st;
		return (ARCHIVE_OK);
	}
	archive_set_error(&a->archive, errno, "Couldn't stat file");
	return (ARCHIVE_WARN);
}