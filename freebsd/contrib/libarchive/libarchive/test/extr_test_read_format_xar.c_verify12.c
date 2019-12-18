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
struct archive {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  archive_entry_atime (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_atime_is_set (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_mtime (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_mtime_is_set (struct archive_entry*) ; 
 int /*<<< orphan*/  assertEqualInt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void verify12(struct archive *a, struct archive_entry *ae)
{
	(void)a; /* UNUSED */
        assertEqualInt(archive_entry_mtime_is_set(ae), 0);
        assertEqualInt(archive_entry_atime_is_set(ae), 0);
	assertEqualInt(archive_entry_mtime(ae), 0);
	assertEqualInt(archive_entry_atime(ae), 0);
}