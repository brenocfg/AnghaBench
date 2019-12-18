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
struct archive_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  archive_entry_xattr_add_entry (struct archive_entry*,char const*,char const*,size_t) ; 
 scalar_t__ memcmp (char const*,char*,int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int
pax_attribute_schily_xattr(struct archive_entry *entry,
	const char *name, const char *value, size_t value_length)
{
	if (strlen(name) < 14 || (memcmp(name, "SCHILY.xattr.", 13)) != 0)
		return 1;

	name += 13;

	archive_entry_xattr_add_entry(entry, name, value, value_length);

	return 0;
}