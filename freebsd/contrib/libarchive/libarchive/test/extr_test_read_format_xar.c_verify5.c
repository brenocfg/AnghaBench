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
 int AE_IFDIR ; 
 int GID ; 
 int /*<<< orphan*/  GNAME ; 
 int UID ; 
 int /*<<< orphan*/  UNAME ; 
 int archive_entry_filetype (struct archive_entry*) ; 
 int archive_entry_gid (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_gname (struct archive_entry*) ; 
 int archive_entry_mode (struct archive_entry*) ; 
 int archive_entry_mtime (struct archive_entry*) ; 
 int archive_entry_uid (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_uname (struct archive_entry*) ; 
 int /*<<< orphan*/  assertEqualInt (int,int) ; 
 int /*<<< orphan*/  assertEqualString (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void verify5(struct archive *a, struct archive_entry *ae)
{
	(void)a; /* UNUSED */
	assertEqualInt(archive_entry_filetype(ae), AE_IFDIR);
	assertEqualInt(archive_entry_mtime(ae), 86401);
	assertEqualInt(archive_entry_mode(ae) & 0777, 0755);
	assertEqualInt(archive_entry_uid(ae), UID);
	assertEqualInt(archive_entry_gid(ae), GID);
	assertEqualString(archive_entry_uname(ae), UNAME);
	assertEqualString(archive_entry_gname(ae), GNAME);
}