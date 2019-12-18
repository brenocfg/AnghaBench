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
struct fixup_entry {int fixup; struct fixup_entry* name; struct fixup_entry* mac_metadata; int /*<<< orphan*/  acl; struct fixup_entry* next; int /*<<< orphan*/  mac_metadata_size; int /*<<< orphan*/  fflags_set; int /*<<< orphan*/  mode; int /*<<< orphan*/  ctime_nanos; int /*<<< orphan*/  ctime; int /*<<< orphan*/  mtime_nanos; int /*<<< orphan*/  mtime; int /*<<< orphan*/  birthtime_nanos; int /*<<< orphan*/  birthtime; int /*<<< orphan*/  atime_nanos; int /*<<< orphan*/  atime; } ;
struct archive_write_disk {int /*<<< orphan*/ * fixup_list; int /*<<< orphan*/  archive; int /*<<< orphan*/ * pst; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_STATE_DATA ; 
 int ARCHIVE_STATE_HEADER ; 
 int /*<<< orphan*/  ARCHIVE_WRITE_DISK_MAGIC ; 
 int O_BINARY ; 
 int O_CLOEXEC ; 
 int O_NOFOLLOW ; 
 int O_WRONLY ; 
 int TODO_ACLS ; 
 int TODO_FFLAGS ; 
 int TODO_MAC_METADATA ; 
 int TODO_MODE_BASE ; 
 int TODO_TIMES ; 
 int _archive_write_disk_finish_entry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  archive_acl_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  archive_check_magic (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  archive_write_disk_set_acls (int /*<<< orphan*/ *,int,struct fixup_entry*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chmod (struct fixup_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fchmod (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct fixup_entry*) ; 
 int open (struct fixup_entry*,int) ; 
 int /*<<< orphan*/  set_fflags_platform (struct archive_write_disk*,int,struct fixup_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_mac_metadata (struct archive_write_disk*,struct fixup_entry*,struct fixup_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_times (struct archive_write_disk*,int,int /*<<< orphan*/ ,struct fixup_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fixup_entry* sort_dir_list (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
_archive_write_disk_close(struct archive *_a)
{
	struct archive_write_disk *a = (struct archive_write_disk *)_a;
	struct fixup_entry *next, *p;
	int fd, ret;

	archive_check_magic(&a->archive, ARCHIVE_WRITE_DISK_MAGIC,
	    ARCHIVE_STATE_HEADER | ARCHIVE_STATE_DATA,
	    "archive_write_disk_close");
	ret = _archive_write_disk_finish_entry(&a->archive);

	/* Sort dir list so directories are fixed up in depth-first order. */
	p = sort_dir_list(a->fixup_list);

	while (p != NULL) {
		fd = -1;
		a->pst = NULL; /* Mark stat cache as out-of-date. */
		if (p->fixup &
		    (TODO_TIMES | TODO_MODE_BASE | TODO_ACLS | TODO_FFLAGS)) {
			fd = open(p->name,
			    O_WRONLY | O_BINARY | O_NOFOLLOW | O_CLOEXEC);
		}
		if (p->fixup & TODO_TIMES) {
			set_times(a, fd, p->mode, p->name,
			    p->atime, p->atime_nanos,
			    p->birthtime, p->birthtime_nanos,
			    p->mtime, p->mtime_nanos,
			    p->ctime, p->ctime_nanos);
		}
		if (p->fixup & TODO_MODE_BASE) {
#ifdef HAVE_FCHMOD
			if (fd >= 0)
				fchmod(fd, p->mode);
			else
#endif
			chmod(p->name, p->mode);
		}
		if (p->fixup & TODO_ACLS)
			archive_write_disk_set_acls(&a->archive, fd,
			    p->name, &p->acl, p->mode);
		if (p->fixup & TODO_FFLAGS)
			set_fflags_platform(a, fd, p->name,
			    p->mode, p->fflags_set, 0);
		if (p->fixup & TODO_MAC_METADATA)
			set_mac_metadata(a, p->name, p->mac_metadata,
					 p->mac_metadata_size);
		next = p->next;
		archive_acl_clear(&p->acl);
		free(p->mac_metadata);
		free(p->name);
		if (fd >= 0)
			close(fd);
		free(p);
		p = next;
	}
	a->fixup_list = NULL;
	return (ret);
}