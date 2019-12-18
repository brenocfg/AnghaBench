#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  s; } ;
struct mtree_entry {int mode; int /*<<< orphan*/  ino; int /*<<< orphan*/  devminor; int /*<<< orphan*/  devmajor; int /*<<< orphan*/  rdevminor; int /*<<< orphan*/  rdevmajor; int /*<<< orphan*/  mtime_nsec; int /*<<< orphan*/  mtime; int /*<<< orphan*/  fflags_clear; int /*<<< orphan*/  fflags_set; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  size; int /*<<< orphan*/  filetype; int /*<<< orphan*/  nlink; int /*<<< orphan*/  fflags_text; int /*<<< orphan*/  gname; int /*<<< orphan*/  uname; int /*<<< orphan*/  symlink; TYPE_1__ pathname; } ;
struct archive_write {int /*<<< orphan*/  archive; } ;

/* Variables and functions */
 int AE_IFMT ; 
 int /*<<< orphan*/  ARCHIVE_ERRNO_MISC ; 
 int ARCHIVE_FAILED ; 
 int ARCHIVE_WARN ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_string_concat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  archive_string_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mtree_entry_exchange_same_entry(struct archive_write *a, struct mtree_entry *np,
    struct mtree_entry *file)
{

	if ((np->mode & AE_IFMT) != (file->mode & AE_IFMT)) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Found duplicate entries `%s' and its file type is "
		    "different",
		    np->pathname.s);
		return (ARCHIVE_FAILED);
	}

	/* Update the existent mtree entry's attributes by the new one's. */
	archive_string_empty(&np->symlink);
	archive_string_concat(&np->symlink, &file->symlink);
	archive_string_empty(&np->uname);
	archive_string_concat(&np->uname, &file->uname);
	archive_string_empty(&np->gname);
	archive_string_concat(&np->gname, &file->gname);
	archive_string_empty(&np->fflags_text);
	archive_string_concat(&np->fflags_text, &file->fflags_text);
	np->nlink = file->nlink;
	np->filetype = file->filetype;
	np->mode = file->mode;
	np->size = file->size;
	np->uid = file->uid;
	np->gid = file->gid;
	np->fflags_set = file->fflags_set;
	np->fflags_clear = file->fflags_clear;
	np->mtime = file->mtime;
	np->mtime_nsec = file->mtime_nsec;
	np->rdevmajor = file->rdevmajor;
	np->rdevminor = file->rdevminor;
	np->devmajor = file->devmajor;
	np->devminor = file->devminor;
	np->ino = file->ino;

	return (ARCHIVE_WARN);
}