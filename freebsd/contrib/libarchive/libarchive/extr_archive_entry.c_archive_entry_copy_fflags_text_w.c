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
typedef  int /*<<< orphan*/  wchar_t ;
struct archive_entry {int /*<<< orphan*/  ae_fflags_clear; int /*<<< orphan*/  ae_fflags_set; int /*<<< orphan*/  ae_fflags_text; } ;

/* Variables and functions */
 int /*<<< orphan*/  const* ae_wcstofflags (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  archive_mstring_copy_wcs (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

const wchar_t *
archive_entry_copy_fflags_text_w(struct archive_entry *entry,
    const wchar_t *flags)
{
	archive_mstring_copy_wcs(&entry->ae_fflags_text, flags);
	return (ae_wcstofflags(flags,
		    &entry->ae_fflags_set, &entry->ae_fflags_clear));
}