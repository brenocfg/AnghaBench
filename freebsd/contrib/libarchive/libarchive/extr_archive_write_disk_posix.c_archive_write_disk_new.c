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
struct archive {int /*<<< orphan*/  vtable; int /*<<< orphan*/  state; int /*<<< orphan*/  magic; } ;
struct archive_write_disk {int decmpfs_compression_level; struct archive archive; int /*<<< orphan*/  path_safe; int /*<<< orphan*/  user_uid; int /*<<< orphan*/  user_umask; int /*<<< orphan*/  start_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_STATE_HEADER ; 
 int /*<<< orphan*/  ARCHIVE_WRITE_DISK_MAGIC ; 
 int /*<<< orphan*/ * archive_string_ensure (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  archive_write_disk_vtable () ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  free (struct archive_write_disk*) ; 
 int /*<<< orphan*/  geteuid () ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  umask (int /*<<< orphan*/ ) ; 

struct archive *
archive_write_disk_new(void)
{
	struct archive_write_disk *a;

	a = (struct archive_write_disk *)calloc(1, sizeof(*a));
	if (a == NULL)
		return (NULL);
	a->archive.magic = ARCHIVE_WRITE_DISK_MAGIC;
	/* We're ready to write a header immediately. */
	a->archive.state = ARCHIVE_STATE_HEADER;
	a->archive.vtable = archive_write_disk_vtable();
	a->start_time = time(NULL);
	/* Query and restore the umask. */
	umask(a->user_umask = umask(0));
#ifdef HAVE_GETEUID
	a->user_uid = geteuid();
#endif /* HAVE_GETEUID */
	if (archive_string_ensure(&a->path_safe, 512) == NULL) {
		free(a);
		return (NULL);
	}
#ifdef HAVE_ZLIB_H
	a->decmpfs_compression_level = 5;
#endif
	return (&a->archive);
}