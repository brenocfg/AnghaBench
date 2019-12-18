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
struct bsdtar {int flags; int /*<<< orphan*/  strip_components; } ;
struct archive_entry {int dummy; } ;

/* Variables and functions */
 int OPTFLAG_ABSOLUTE_PATHS ; 
 int apply_substitution (struct bsdtar*,char const*,char**,int,int) ; 
 int /*<<< orphan*/  archive_entry_copy_hardlink (struct archive_entry*,char const*) ; 
 int /*<<< orphan*/  archive_entry_copy_pathname (struct archive_entry*,char const*) ; 
 int /*<<< orphan*/  archive_entry_copy_symlink (struct archive_entry*,char*) ; 
 char* archive_entry_hardlink (struct archive_entry*) ; 
 char* archive_entry_pathname (struct archive_entry*) ; 
 char const* archive_entry_symlink (struct archive_entry*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  lafe_warnc (int /*<<< orphan*/ ,char*) ; 
 char* strip_absolute_path (struct bsdtar*,char const*) ; 
 char* strip_components (char const*,int /*<<< orphan*/ ) ; 

int
edit_pathname(struct bsdtar *bsdtar, struct archive_entry *entry)
{
	const char *name = archive_entry_pathname(entry);
	const char *original_name = name;
	const char *hardlinkname = archive_entry_hardlink(entry);
	const char *original_hardlinkname = hardlinkname;
#if defined(HAVE_REGEX_H) || defined(HAVE_PCREPOSIX_H)
	char *subst_name;
	int r;

	/* Apply user-specified substitution to pathname. */
	r = apply_substitution(bsdtar, name, &subst_name, 0, 0);
	if (r == -1) {
		lafe_warnc(0, "Invalid substitution, skipping entry");
		return 1;
	}
	if (r == 1) {
		archive_entry_copy_pathname(entry, subst_name);
		if (*subst_name == '\0') {
			free(subst_name);
			return -1;
		} else
			free(subst_name);
		name = archive_entry_pathname(entry);
		original_name = name;
	}

	/* Apply user-specified substitution to hardlink target. */
	if (hardlinkname != NULL) {
		r = apply_substitution(bsdtar, hardlinkname, &subst_name, 0, 1);
		if (r == -1) {
			lafe_warnc(0, "Invalid substitution, skipping entry");
			return 1;
		}
		if (r == 1) {
			archive_entry_copy_hardlink(entry, subst_name);
			free(subst_name);
		}
		hardlinkname = archive_entry_hardlink(entry);
		original_hardlinkname = hardlinkname;
	}

	/* Apply user-specified substitution to symlink body. */
	if (archive_entry_symlink(entry) != NULL) {
		r = apply_substitution(bsdtar, archive_entry_symlink(entry), &subst_name, 1, 0);
		if (r == -1) {
			lafe_warnc(0, "Invalid substitution, skipping entry");
			return 1;
		}
		if (r == 1) {
			archive_entry_copy_symlink(entry, subst_name);
			free(subst_name);
		}
	}
#endif

	/* Strip leading dir names as per --strip-components option. */
	if (bsdtar->strip_components > 0) {
		name = strip_components(name, bsdtar->strip_components);
		if (name == NULL)
			return (1);

		if (hardlinkname != NULL) {
			hardlinkname = strip_components(hardlinkname,
			    bsdtar->strip_components);
			if (hardlinkname == NULL)
				return (1);
		}
	}

	if ((bsdtar->flags & OPTFLAG_ABSOLUTE_PATHS) == 0) {
		/* By default, don't write or restore absolute pathnames. */
		name = strip_absolute_path(bsdtar, name);
		if (*name == '\0')
			name = ".";

		if (hardlinkname != NULL) {
			hardlinkname = strip_absolute_path(bsdtar, hardlinkname);
			if (*hardlinkname == '\0')
				return (1);
		}
	} else {
		/* Strip redundant leading '/' characters. */
		while (name[0] == '/' && name[1] == '/')
			name++;
	}

	/* Replace name in archive_entry. */
	if (name != original_name) {
		archive_entry_copy_pathname(entry, name);
	}
	if (hardlinkname != original_hardlinkname) {
		archive_entry_copy_hardlink(entry, hardlinkname);
	}
	return (0);
}