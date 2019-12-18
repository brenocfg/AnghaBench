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
struct archive_string_conv {int dummy; } ;
struct archive_entry {int /*<<< orphan*/  ae_gname; } ;

/* Variables and functions */
 int archive_mstring_copy_mbs_len_l (int /*<<< orphan*/ *,char const*,size_t,struct archive_string_conv*) ; 

int
_archive_entry_copy_gname_l(struct archive_entry *entry,
    const char *name, size_t len, struct archive_string_conv *sc)
{
	return (archive_mstring_copy_mbs_len_l(&entry->ae_gname, name, len, sc));
}