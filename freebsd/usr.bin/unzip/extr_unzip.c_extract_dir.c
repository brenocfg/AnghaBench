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
 int /*<<< orphan*/  ac (int /*<<< orphan*/ ) ; 
 int archive_entry_mode (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_read_data_skip (struct archive*) ; 
 int /*<<< orphan*/  info (char*,char const*) ; 
 int /*<<< orphan*/  make_dir (char const*,int) ; 

__attribute__((used)) static void
extract_dir(struct archive *a, struct archive_entry *e, const char *path)
{
	int mode;

	mode = archive_entry_mode(e) & 0777;
	if (mode == 0)
		mode = 0755;

	/*
	 * Some zipfiles contain directories with weird permissions such
	 * as 0644 or 0444.  This can cause strange issues such as being
	 * unable to extract files into the directory we just created, or
	 * the user being unable to remove the directory later without
	 * first manually changing its permissions.  Therefore, we whack
	 * the permissions into shape, assuming that the user wants full
	 * access and that anyone who gets read access also gets execute
	 * access.
	 */
	mode |= 0700;
	if (mode & 0040)
		mode |= 0010;
	if (mode & 0004)
		mode |= 0001;

	info("   creating: %s/\n", path);
	make_dir(path, mode);
	ac(archive_read_data_skip(a));
}