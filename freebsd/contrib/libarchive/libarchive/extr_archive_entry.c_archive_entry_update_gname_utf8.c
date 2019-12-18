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
struct archive_entry {int /*<<< orphan*/  ae_gname; int /*<<< orphan*/  archive; } ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  __archive_errx (int,char*) ; 
 scalar_t__ archive_mstring_update_utf8 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ errno ; 

int
archive_entry_update_gname_utf8(struct archive_entry *entry, const char *name)
{
	if (archive_mstring_update_utf8(entry->archive,
	    &entry->ae_gname, name) == 0)
		return (1);
	if (errno == ENOMEM)
		__archive_errx(1, "No memory");
	return (0);
}