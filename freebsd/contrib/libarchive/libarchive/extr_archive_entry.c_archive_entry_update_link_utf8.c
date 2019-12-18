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
struct archive_entry {int ae_set; int /*<<< orphan*/  ae_hardlink; int /*<<< orphan*/  archive; int /*<<< orphan*/  ae_symlink; } ;

/* Variables and functions */
 int AE_SET_SYMLINK ; 
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  __archive_errx (int,char*) ; 
 int archive_mstring_update_utf8 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ errno ; 

int
archive_entry_update_link_utf8(struct archive_entry *entry, const char *target)
{
	int r;
	if (entry->ae_set & AE_SET_SYMLINK)
		r = archive_mstring_update_utf8(entry->archive,
		    &entry->ae_symlink, target);
	else
		r = archive_mstring_update_utf8(entry->archive,
		    &entry->ae_hardlink, target);
	if (r == 0)
		return (1);
	if (errno == ENOMEM)
		__archive_errx(1, "No memory");
	return (0);
}