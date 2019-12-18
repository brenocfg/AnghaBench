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
struct bsdtar {int flags; } ;
struct archive_entry {int dummy; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int OPTFLAG_INTERACTIVE ; 
 int OPTFLAG_NO_SUBDIRS ; 
 int /*<<< orphan*/  archive_entry_pathname (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_read_disk_can_descend (struct archive*) ; 
 int /*<<< orphan*/  archive_read_disk_descend (struct archive*) ; 
 int /*<<< orphan*/  yes (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
excluded_callback(struct archive *a, void *_data, struct archive_entry *entry)
{
	struct bsdtar *bsdtar = (struct bsdtar *)_data;

	if (bsdtar->flags & OPTFLAG_NO_SUBDIRS)
		return;
	if (!archive_read_disk_can_descend(a))
		return;
	if ((bsdtar->flags & OPTFLAG_INTERACTIVE) &&
	    !yes("add '%s'", archive_entry_pathname(entry)))
		return;
	archive_read_disk_descend(a);
}