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
typedef  int /*<<< orphan*/  uid_t ;
typedef  int time_t ;
struct cpio {scalar_t__ day_first; scalar_t__ option_numeric_uid_gid; } ;
struct archive_entry {int dummy; } ;
typedef  int /*<<< orphan*/  size ;
typedef  int /*<<< orphan*/  date ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ AE_IFBLK ; 
 scalar_t__ AE_IFCHR ; 
 scalar_t__ archive_entry_filetype (struct archive_entry*) ; 
 scalar_t__ archive_entry_gid (struct archive_entry*) ; 
 char* archive_entry_gname (struct archive_entry*) ; 
 char* archive_entry_hardlink (struct archive_entry*) ; 
 int archive_entry_mtime (struct archive_entry*) ; 
 char* archive_entry_nlink (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_pathname (struct archive_entry*) ; 
 scalar_t__ archive_entry_rdevmajor (struct archive_entry*) ; 
 scalar_t__ archive_entry_rdevminor (struct archive_entry*) ; 
 scalar_t__ archive_entry_size (struct archive_entry*) ; 
 char* archive_entry_strmode (struct archive_entry*) ; 
 char* archive_entry_symlink (struct archive_entry*) ; 
 scalar_t__ archive_entry_uid (struct archive_entry*) ; 
 char* archive_entry_uname (struct archive_entry*) ; 
 int /*<<< orphan*/  cpio_i64toa (scalar_t__) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  localtime (int*) ; 
 char* lookup_gname (struct cpio*,int /*<<< orphan*/ ) ; 
 char* lookup_uname (struct cpio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/ * stdout ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strftime (char*,int,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (int*) ; 

__attribute__((used)) static void
list_item_verbose(struct cpio *cpio, struct archive_entry *entry)
{
	char			 size[32];
	char			 date[32];
	char			 uids[16], gids[16];
	const char 		*uname, *gname;
	FILE			*out = stdout;
	const char		*fmt;
	time_t			 mtime;
	static time_t		 now;

	if (!now)
		time(&now);

	if (cpio->option_numeric_uid_gid) {
		/* Format numeric uid/gid for display. */
		strcpy(uids, cpio_i64toa(archive_entry_uid(entry)));
		uname = uids;
		strcpy(gids, cpio_i64toa(archive_entry_gid(entry)));
		gname = gids;
	} else {
		/* Use uname if it's present, else lookup name from uid. */
		uname = archive_entry_uname(entry);
		if (uname == NULL)
			uname = lookup_uname(cpio, (uid_t)archive_entry_uid(entry));
		/* Use gname if it's present, else lookup name from gid. */
		gname = archive_entry_gname(entry);
		if (gname == NULL)
			gname = lookup_gname(cpio, (uid_t)archive_entry_gid(entry));
	}

	/* Print device number or file size. */
	if (archive_entry_filetype(entry) == AE_IFCHR
	    || archive_entry_filetype(entry) == AE_IFBLK) {
		snprintf(size, sizeof(size), "%lu,%lu",
		    (unsigned long)archive_entry_rdevmajor(entry),
		    (unsigned long)archive_entry_rdevminor(entry));
	} else {
		strcpy(size, cpio_i64toa(archive_entry_size(entry)));
	}

	/* Format the time using 'ls -l' conventions. */
	mtime = archive_entry_mtime(entry);
#if defined(_WIN32) && !defined(__CYGWIN__)
	/* Windows' strftime function does not support %e format. */
	if (mtime - now > 365*86400/2
		|| mtime - now < -365*86400/2)
		fmt = cpio->day_first ? "%d %b  %Y" : "%b %d  %Y";
	else
		fmt = cpio->day_first ? "%d %b %H:%M" : "%b %d %H:%M";
#else
	if (mtime - now > 365*86400/2
		|| mtime - now < -365*86400/2)
		fmt = cpio->day_first ? "%e %b  %Y" : "%b %e  %Y";
	else
		fmt = cpio->day_first ? "%e %b %H:%M" : "%b %e %H:%M";
#endif
	strftime(date, sizeof(date), fmt, localtime(&mtime));

	fprintf(out, "%s%3d %-8s %-8s %8s %12s %s",
	    archive_entry_strmode(entry),
	    archive_entry_nlink(entry),
	    uname, gname, size, date,
	    archive_entry_pathname(entry));

	/* Extra information for links. */
	if (archive_entry_hardlink(entry)) /* Hard link */
		fprintf(out, " link to %s", archive_entry_hardlink(entry));
	else if (archive_entry_symlink(entry)) /* Symbolic link */
		fprintf(out, " -> %s", archive_entry_symlink(entry));
	fprintf(out, "\n");
}