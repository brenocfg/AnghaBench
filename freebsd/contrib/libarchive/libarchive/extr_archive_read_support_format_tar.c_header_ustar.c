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
struct archive_string {char* s; } ;
struct tar {int entry_padding; int entry_bytes_remaining; int /*<<< orphan*/  sconv; struct archive_string entry_pathname; } ;
struct archive_read {int dummy; } ;
struct archive_entry_header_ustar {char* typeflag; int /*<<< orphan*/  rdevminor; int /*<<< orphan*/  rdevmajor; int /*<<< orphan*/  gname; int /*<<< orphan*/  uname; scalar_t__* name; scalar_t__* prefix; } ;
struct archive_entry {int dummy; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 scalar_t__ archive_entry_copy_gname_l (struct archive_entry*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ archive_entry_copy_pathname_l (struct archive_entry*,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ archive_entry_copy_uname_l (struct archive_entry*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_set_rdevmajor (struct archive_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_set_rdevminor (struct archive_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_strappend_char (struct archive_string*,char) ; 
 int archive_strlen (struct archive_string*) ; 
 int /*<<< orphan*/  archive_strncat (struct archive_string*,scalar_t__*,int) ; 
 int /*<<< orphan*/  archive_strncpy (struct archive_string*,scalar_t__*,int) ; 
 int header_common (struct archive_read*,struct tar*,struct archive_entry*,void const*) ; 
 int set_conversion_failed_error (struct archive_read*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ tar_atol (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
header_ustar(struct archive_read *a, struct tar *tar,
    struct archive_entry *entry, const void *h)
{
	const struct archive_entry_header_ustar	*header;
	struct archive_string *as;
	int err = ARCHIVE_OK, r;

	header = (const struct archive_entry_header_ustar *)h;

	/* Copy name into an internal buffer to ensure null-termination. */
	as = &(tar->entry_pathname);
	if (header->prefix[0]) {
		archive_strncpy(as, header->prefix, sizeof(header->prefix));
		if (as->s[archive_strlen(as) - 1] != '/')
			archive_strappend_char(as, '/');
		archive_strncat(as, header->name, sizeof(header->name));
	} else {
		archive_strncpy(as, header->name, sizeof(header->name));
	}
	if (archive_entry_copy_pathname_l(entry, as->s, archive_strlen(as),
	    tar->sconv) != 0) {
		err = set_conversion_failed_error(a, tar->sconv, "Pathname");
		if (err == ARCHIVE_FATAL)
			return (err);
	}

	/* Handle rest of common fields. */
	r = header_common(a, tar, entry, h);
	if (r == ARCHIVE_FATAL)
		return (r);
	if (r < err)
		err = r;

	/* Handle POSIX ustar fields. */
	if (archive_entry_copy_uname_l(entry,
	    header->uname, sizeof(header->uname), tar->sconv) != 0) {
		err = set_conversion_failed_error(a, tar->sconv, "Uname");
		if (err == ARCHIVE_FATAL)
			return (err);
	}

	if (archive_entry_copy_gname_l(entry,
	    header->gname, sizeof(header->gname), tar->sconv) != 0) {
		err = set_conversion_failed_error(a, tar->sconv, "Gname");
		if (err == ARCHIVE_FATAL)
			return (err);
	}

	/* Parse out device numbers only for char and block specials. */
	if (header->typeflag[0] == '3' || header->typeflag[0] == '4') {
		archive_entry_set_rdevmajor(entry, (dev_t)
		    tar_atol(header->rdevmajor, sizeof(header->rdevmajor)));
		archive_entry_set_rdevminor(entry, (dev_t)
		    tar_atol(header->rdevminor, sizeof(header->rdevminor)));
	}

	tar->entry_padding = 0x1ff & (-tar->entry_bytes_remaining);

	return (err);
}