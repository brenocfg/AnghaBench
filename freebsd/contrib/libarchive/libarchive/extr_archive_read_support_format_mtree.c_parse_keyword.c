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
typedef  int /*<<< orphan*/  time_t ;
struct mtree_option {char* value; } ;
struct mtree {int /*<<< orphan*/  contents_name; } ;
struct archive_read {int /*<<< orphan*/  archive; } ;
struct archive_entry {int dummy; } ;
typedef  int /*<<< orphan*/  mode_t ;
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  AE_IFBLK ; 
 int /*<<< orphan*/  AE_IFCHR ; 
 int /*<<< orphan*/  AE_IFDIR ; 
 int /*<<< orphan*/  AE_IFIFO ; 
 int /*<<< orphan*/  AE_IFLNK ; 
 int /*<<< orphan*/  AE_IFREG ; 
 int /*<<< orphan*/  ARCHIVE_ERRNO_FILE_FORMAT ; 
 int ARCHIVE_OK ; 
 int ARCHIVE_WARN ; 
 int MTREE_HAS_DEVICE ; 
 int MTREE_HAS_FFLAGS ; 
 int MTREE_HAS_GID ; 
 int MTREE_HAS_GNAME ; 
 int MTREE_HAS_MTIME ; 
 int MTREE_HAS_NLINK ; 
 int MTREE_HAS_NOCHANGE ; 
 int MTREE_HAS_OPTIONAL ; 
 int MTREE_HAS_PERM ; 
 int MTREE_HAS_TYPE ; 
 int MTREE_HAS_UID ; 
 int MTREE_HAS_UNAME ; 
 int /*<<< orphan*/  __LA_FALLTHROUGH ; 
 int /*<<< orphan*/  archive_entry_copy_fflags_text (struct archive_entry*,char*) ; 
 int /*<<< orphan*/  archive_entry_copy_gname (struct archive_entry*,char*) ; 
 int /*<<< orphan*/  archive_entry_copy_symlink (struct archive_entry*,char*) ; 
 int /*<<< orphan*/  archive_entry_copy_uname (struct archive_entry*,char*) ; 
 int /*<<< orphan*/  archive_entry_set_dev (struct archive_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_set_filetype (struct archive_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_set_gid (struct archive_entry*,scalar_t__) ; 
 int /*<<< orphan*/  archive_entry_set_ino (struct archive_entry*,scalar_t__) ; 
 int /*<<< orphan*/  archive_entry_set_mtime (struct archive_entry*,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  archive_entry_set_nlink (struct archive_entry*,unsigned int) ; 
 int /*<<< orphan*/  archive_entry_set_perm (struct archive_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_set_rdev (struct archive_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_set_size (struct archive_entry*,scalar_t__) ; 
 int /*<<< orphan*/  archive_entry_set_uid (struct archive_entry*,scalar_t__) ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  archive_strcpy (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ get_time_t_max () ; 
 scalar_t__ get_time_t_min () ; 
 scalar_t__ mtree_atol (char**,int) ; 
 int parse_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  parse_escapes (char*,int /*<<< orphan*/ *) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int
parse_keyword(struct archive_read *a, struct mtree *mtree,
    struct archive_entry *entry, struct mtree_option *opt, int *parsed_kws)
{
	char *val, *key;

	key = opt->value;

	if (*key == '\0')
		return (ARCHIVE_OK);

	if (strcmp(key, "nochange") == 0) {
		*parsed_kws |= MTREE_HAS_NOCHANGE;
		return (ARCHIVE_OK);
	}
	if (strcmp(key, "optional") == 0) {
		*parsed_kws |= MTREE_HAS_OPTIONAL;
		return (ARCHIVE_OK);
	}
	if (strcmp(key, "ignore") == 0) {
		/*
		 * The mtree processing is not recursive, so
		 * recursion will only happen for explicitly listed
		 * entries.
		 */
		return (ARCHIVE_OK);
	}

	val = strchr(key, '=');
	if (val == NULL) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Malformed attribute \"%s\" (%d)", key, key[0]);
		return (ARCHIVE_WARN);
	}

	*val = '\0';
	++val;

	switch (key[0]) {
	case 'c':
		if (strcmp(key, "content") == 0
		    || strcmp(key, "contents") == 0) {
			parse_escapes(val, NULL);
			archive_strcpy(&mtree->contents_name, val);
			break;
		}
		if (strcmp(key, "cksum") == 0)
			break;
		__LA_FALLTHROUGH;
	case 'd':
		if (strcmp(key, "device") == 0) {
			/* stat(2) st_rdev field, e.g. the major/minor IDs
			 * of a char/block special file */
			int r;
			dev_t dev;

			*parsed_kws |= MTREE_HAS_DEVICE;
			r = parse_device(&dev, &a->archive, val);
			if (r == ARCHIVE_OK)
				archive_entry_set_rdev(entry, dev);
			return r;
		}
		__LA_FALLTHROUGH;
	case 'f':
		if (strcmp(key, "flags") == 0) {
			*parsed_kws |= MTREE_HAS_FFLAGS;
			archive_entry_copy_fflags_text(entry, val);
			break;
		}
		__LA_FALLTHROUGH;
	case 'g':
		if (strcmp(key, "gid") == 0) {
			*parsed_kws |= MTREE_HAS_GID;
			archive_entry_set_gid(entry, mtree_atol(&val, 10));
			break;
		}
		if (strcmp(key, "gname") == 0) {
			*parsed_kws |= MTREE_HAS_GNAME;
			archive_entry_copy_gname(entry, val);
			break;
		}
		__LA_FALLTHROUGH;
	case 'i':
		if (strcmp(key, "inode") == 0) {
			archive_entry_set_ino(entry, mtree_atol(&val, 10));
			break;
		}
		__LA_FALLTHROUGH;
	case 'l':
		if (strcmp(key, "link") == 0) {
			archive_entry_copy_symlink(entry, val);
			break;
		}
		__LA_FALLTHROUGH;
	case 'm':
		if (strcmp(key, "md5") == 0 || strcmp(key, "md5digest") == 0)
			break;
		if (strcmp(key, "mode") == 0) {
			if (val[0] >= '0' && val[0] <= '7') {
				*parsed_kws |= MTREE_HAS_PERM;
				archive_entry_set_perm(entry,
				    (mode_t)mtree_atol(&val, 8));
			} else {
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_FILE_FORMAT,
				    "Symbolic or non-octal mode \"%s\" unsupported", val);
				return ARCHIVE_WARN;
			}
			break;
		}
		__LA_FALLTHROUGH;
	case 'n':
		if (strcmp(key, "nlink") == 0) {
			*parsed_kws |= MTREE_HAS_NLINK;
			archive_entry_set_nlink(entry,
				(unsigned int)mtree_atol(&val, 10));
			break;
		}
		__LA_FALLTHROUGH;
	case 'r':
		if (strcmp(key, "resdevice") == 0) {
			/* stat(2) st_dev field, e.g. the device ID where the
			 * inode resides */
			int r;
			dev_t dev;

			r = parse_device(&dev, &a->archive, val);
			if (r == ARCHIVE_OK)
				archive_entry_set_dev(entry, dev);
			return r;
		}
		if (strcmp(key, "rmd160") == 0 ||
		    strcmp(key, "rmd160digest") == 0)
			break;
		__LA_FALLTHROUGH;
	case 's':
		if (strcmp(key, "sha1") == 0 || strcmp(key, "sha1digest") == 0)
			break;
		if (strcmp(key, "sha256") == 0 ||
		    strcmp(key, "sha256digest") == 0)
			break;
		if (strcmp(key, "sha384") == 0 ||
		    strcmp(key, "sha384digest") == 0)
			break;
		if (strcmp(key, "sha512") == 0 ||
		    strcmp(key, "sha512digest") == 0)
			break;
		if (strcmp(key, "size") == 0) {
			archive_entry_set_size(entry, mtree_atol(&val, 10));
			break;
		}
		__LA_FALLTHROUGH;
	case 't':
		if (strcmp(key, "tags") == 0) {
			/*
			 * Comma delimited list of tags.
			 * Ignore the tags for now, but the interface
			 * should be extended to allow inclusion/exclusion.
			 */
			break;
		}
		if (strcmp(key, "time") == 0) {
			int64_t m;
			int64_t my_time_t_max = get_time_t_max();
			int64_t my_time_t_min = get_time_t_min();
			long ns = 0;

			*parsed_kws |= MTREE_HAS_MTIME;
			m = mtree_atol(&val, 10);
			/* Replicate an old mtree bug:
			 * 123456789.1 represents 123456789
			 * seconds and 1 nanosecond. */
			if (*val == '.') {
				++val;
				ns = (long)mtree_atol(&val, 10);
				if (ns < 0)
					ns = 0;
				else if (ns > 999999999)
					ns = 999999999;
			}
			if (m > my_time_t_max)
				m = my_time_t_max;
			else if (m < my_time_t_min)
				m = my_time_t_min;
			archive_entry_set_mtime(entry, (time_t)m, ns);
			break;
		}
		if (strcmp(key, "type") == 0) {
			switch (val[0]) {
			case 'b':
				if (strcmp(val, "block") == 0) {
					archive_entry_set_filetype(entry, AE_IFBLK);
					break;
				}
				__LA_FALLTHROUGH;
			case 'c':
				if (strcmp(val, "char") == 0) {
					archive_entry_set_filetype(entry,
						AE_IFCHR);
					break;
				}
				__LA_FALLTHROUGH;
			case 'd':
				if (strcmp(val, "dir") == 0) {
					archive_entry_set_filetype(entry,
						AE_IFDIR);
					break;
				}
				__LA_FALLTHROUGH;
			case 'f':
				if (strcmp(val, "fifo") == 0) {
					archive_entry_set_filetype(entry,
						AE_IFIFO);
					break;
				}
				if (strcmp(val, "file") == 0) {
					archive_entry_set_filetype(entry,
						AE_IFREG);
					break;
				}
				__LA_FALLTHROUGH;
			case 'l':
				if (strcmp(val, "link") == 0) {
					archive_entry_set_filetype(entry,
						AE_IFLNK);
					break;
				}
				__LA_FALLTHROUGH;
			default:
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_FILE_FORMAT,
				    "Unrecognized file type \"%s\"; "
				    "assuming \"file\"", val);
				archive_entry_set_filetype(entry, AE_IFREG);
				return (ARCHIVE_WARN);
			}
			*parsed_kws |= MTREE_HAS_TYPE;
			break;
		}
		__LA_FALLTHROUGH;
	case 'u':
		if (strcmp(key, "uid") == 0) {
			*parsed_kws |= MTREE_HAS_UID;
			archive_entry_set_uid(entry, mtree_atol(&val, 10));
			break;
		}
		if (strcmp(key, "uname") == 0) {
			*parsed_kws |= MTREE_HAS_UNAME;
			archive_entry_copy_uname(entry, val);
			break;
		}
		__LA_FALLTHROUGH;
	default:
		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Unrecognized key %s=%s", key, val);
		return (ARCHIVE_WARN);
	}
	return (ARCHIVE_OK);
}