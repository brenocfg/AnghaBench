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
struct archive_entry {int /*<<< orphan*/  ae_fflags_clear; int /*<<< orphan*/  ae_fflags_set; int /*<<< orphan*/  ae_fflags_text; } ;

/* Variables and functions */
 char const* ae_strtofflags (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  archive_mstring_copy_mbs (int /*<<< orphan*/ *,char const*) ; 

const char *
archive_entry_copy_fflags_text(struct archive_entry *entry,
    const char *flags)
{
	archive_mstring_copy_mbs(&entry->ae_fflags_text, flags);
	return (ae_strtofflags(flags,
		    &entry->ae_fflags_set, &entry->ae_fflags_clear));
}