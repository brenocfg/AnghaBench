#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int wchar_t ;
typedef  size_t uint64_t ;
typedef  int time_t ;
struct TYPE_10__ {char* s; } ;
struct pax {int sparse_map_padding; int entry_bytes_remaining; int entry_padding; int /*<<< orphan*/ * sparse_list; TYPE_1__ pax_header; TYPE_1__ sparse_map; scalar_t__ opt_binary; struct archive_string_conv* sconv_utf8; } ;
struct archive_wstring {char* s; } ;
struct TYPE_11__ {scalar_t__ archive_format; } ;
struct archive_write {TYPE_4__ archive; scalar_t__ format_data; } ;
struct archive_string_conv {int dummy; } ;
struct archive_string {char* s; } ;
struct archive_entry {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  intmax_t ;
typedef  int int64_t ;

/* Variables and functions */
#define  AE_IFBLK 134 
#define  AE_IFCHR 133 
#define  AE_IFDIR 132 
#define  AE_IFIFO 131 
#define  AE_IFLNK 130 
#define  AE_IFREG 129 
#define  AE_IFSOCK 128 
 scalar_t__ AE_SYMLINK_TYPE_DIRECTORY ; 
 scalar_t__ AE_SYMLINK_TYPE_FILE ; 
 int ARCHIVE_ENTRY_ACL_STYLE_COMPACT ; 
 int ARCHIVE_ENTRY_ACL_STYLE_EXTRA_ID ; 
 int ARCHIVE_ENTRY_ACL_STYLE_SEPARATOR_COMMA ; 
 int ARCHIVE_ENTRY_ACL_TYPE_ACCESS ; 
 int ARCHIVE_ENTRY_ACL_TYPE_DEFAULT ; 
 int ARCHIVE_ENTRY_ACL_TYPE_NFS4 ; 
 int /*<<< orphan*/  ARCHIVE_ERRNO_FILE_FORMAT ; 
 int /*<<< orphan*/  ARCHIVE_ERRNO_MISC ; 
 int ARCHIVE_FAILED ; 
 int ARCHIVE_FATAL ; 
 scalar_t__ ARCHIVE_FORMAT_TAR_PAX_INTERCHANGE ; 
 scalar_t__ ARCHIVE_FORMAT_TAR_PAX_RESTRICTED ; 
 int ARCHIVE_OK ; 
 int ARCHIVE_WARN ; 
 int /*<<< orphan*/  ENOMEM ; 
 int S_ISGID ; 
 int S_ISUID ; 
 int S_ISVTX ; 
 int __archive_write_format_header_ustar (struct archive_write*,char*,struct archive_entry*,char,int,int /*<<< orphan*/ *) ; 
 int __archive_write_nulls (struct archive_write*,size_t) ; 
 int __archive_write_output (struct archive_write*,char*,int) ; 
 struct archive_entry* __la_win_entry_in_posix_pathseparator (struct archive_entry*) ; 
 int add_pax_acl (struct archive_write*,struct archive_entry*,struct pax*,int) ; 
 int /*<<< orphan*/  add_pax_attr (TYPE_1__*,char*,char const*) ; 
 int /*<<< orphan*/  add_pax_attr_int (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  add_pax_attr_time (TYPE_1__*,char*,int,scalar_t__) ; 
 int archive_entry_acl_types (struct archive_entry*) ; 
 int archive_entry_atime (struct archive_entry*) ; 
 scalar_t__ archive_entry_atime_nsec (struct archive_entry*) ; 
 int archive_entry_birthtime (struct archive_entry*) ; 
 scalar_t__ archive_entry_birthtime_is_set (struct archive_entry*) ; 
 scalar_t__ archive_entry_birthtime_nsec (struct archive_entry*) ; 
 struct archive_entry* archive_entry_clone (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_copy_pathname (struct archive_entry*,char*) ; 
 int /*<<< orphan*/  archive_entry_copy_pathname_w (struct archive_entry*,char*) ; 
 int archive_entry_ctime (struct archive_entry*) ; 
 scalar_t__ archive_entry_ctime_nsec (struct archive_entry*) ; 
 char* archive_entry_fflags_text (struct archive_entry*) ; 
 int const archive_entry_filetype (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_free (struct archive_entry*) ; 
 int archive_entry_gid (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_gname (struct archive_entry*) ; 
 void* archive_entry_mac_metadata (struct archive_entry*,size_t*) ; 
 int archive_entry_mode (struct archive_entry*) ; 
 int archive_entry_mtime (struct archive_entry*) ; 
 scalar_t__ archive_entry_mtime_nsec (struct archive_entry*) ; 
 struct archive_entry* archive_entry_new2 (TYPE_4__*) ; 
 char* archive_entry_pathname (struct archive_entry*) ; 
 int* archive_entry_pathname_w (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_perm (struct archive_entry*) ; 
 int archive_entry_rdevmajor (struct archive_entry*) ; 
 int archive_entry_rdevminor (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_set_atime (struct archive_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_set_ctime (struct archive_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_set_filetype (struct archive_entry*,int const) ; 
 int /*<<< orphan*/  archive_entry_set_gid (struct archive_entry*,int) ; 
 int /*<<< orphan*/  archive_entry_set_gname (struct archive_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_set_hardlink (struct archive_entry*,char*) ; 
 int /*<<< orphan*/  archive_entry_set_mode (struct archive_entry*,int) ; 
 int /*<<< orphan*/  archive_entry_set_mtime (struct archive_entry*,int,scalar_t__) ; 
 int /*<<< orphan*/  archive_entry_set_pathname (struct archive_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_set_perm (struct archive_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_set_size (struct archive_entry*,size_t) ; 
 int /*<<< orphan*/  archive_entry_set_symlink (struct archive_entry*,char*) ; 
 int /*<<< orphan*/  archive_entry_set_uid (struct archive_entry*,int) ; 
 int /*<<< orphan*/  archive_entry_set_uname (struct archive_entry*,int /*<<< orphan*/ ) ; 
 int archive_entry_size (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_sparse_add_entry (struct archive_entry*,int,int /*<<< orphan*/ ) ; 
 int archive_entry_sparse_next (struct archive_entry*,int*,int*) ; 
 int archive_entry_sparse_reset (struct archive_entry*) ; 
 scalar_t__ archive_entry_symlink_type (struct archive_entry*) ; 
 int archive_entry_uid (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_uname (struct archive_entry*) ; 
 scalar_t__ archive_entry_xattr_count (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_set_error (TYPE_4__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  archive_strappend_char (struct archive_wstring*,char) ; 
 int /*<<< orphan*/  archive_strcpy (struct archive_wstring*,char*) ; 
 int /*<<< orphan*/  archive_string_conversion_charset_name (struct archive_string_conv*) ; 
 struct archive_string_conv* archive_string_conversion_to_charset (TYPE_4__*,char*,int) ; 
 int /*<<< orphan*/  archive_string_empty (TYPE_1__*) ; 
 int /*<<< orphan*/ * archive_string_ensure (struct archive_wstring*,size_t) ; 
 int /*<<< orphan*/  archive_string_free (struct archive_wstring*) ; 
 int /*<<< orphan*/  archive_string_init (struct archive_wstring*) ; 
 int /*<<< orphan*/  archive_string_sprintf (TYPE_1__*,char*,int,...) ; 
 int archive_strlen (TYPE_1__*) ; 
 int /*<<< orphan*/  archive_strncpy (struct archive_wstring*,char const*,size_t) ; 
 scalar_t__ archive_write_pax_data (struct archive_write*,void const*,size_t) ; 
 int archive_write_pax_finish_entry (struct archive_write*) ; 
 int archive_write_pax_header_xattrs (struct archive_write*,struct pax*,struct archive_entry*) ; 
 int /*<<< orphan*/  archive_wstrappend_wchar (struct archive_wstring*,int) ; 
 int /*<<< orphan*/ * archive_wstring_ensure (struct archive_wstring*,size_t) ; 
 int /*<<< orphan*/  archive_wstring_free (struct archive_wstring*) ; 
 int /*<<< orphan*/  archive_wstrncpy (struct archive_wstring*,int const*,size_t) ; 
 int /*<<< orphan*/  build_gnu_sparse_name (char*,char*) ; 
 int /*<<< orphan*/  build_pax_attribute_name (char*,char const*) ; 
 int /*<<< orphan*/  build_ustar_entry_name (char*,char const*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int get_entry_gname (struct archive_write*,struct archive_entry*,char const**,size_t*,struct archive_string_conv*) ; 
 int get_entry_hardlink (struct archive_write*,struct archive_entry*,char const**,size_t*,struct archive_string_conv*) ; 
 int get_entry_pathname (struct archive_write*,struct archive_entry*,char const**,size_t*,struct archive_string_conv*) ; 
 int get_entry_symlink (struct archive_write*,struct archive_entry*,char const**,size_t*,struct archive_string_conv*) ; 
 int get_entry_uname (struct archive_write*,struct archive_entry*,char const**,size_t*,struct archive_string_conv*) ; 
 scalar_t__ has_non_ASCII (char const*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 int sparse_list_add (struct pax*,int,size_t) ; 
 int /*<<< orphan*/  sparse_list_clear (struct pax*) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 
 char* strrchr (char*,char) ; 
 size_t wcslen (int const*) ; 

__attribute__((used)) static int
archive_write_pax_header(struct archive_write *a,
    struct archive_entry *entry_original)
{
	struct archive_entry *entry_main;
	const char *p;
	const char *suffix;
	int need_extension, r, ret;
	int acl_types;
	int sparse_count;
	uint64_t sparse_total, real_size;
	struct pax *pax;
	const char *hardlink;
	const char *path = NULL, *linkpath = NULL;
	const char *uname = NULL, *gname = NULL;
	const void *mac_metadata;
	size_t mac_metadata_size;
	struct archive_string_conv *sconv;
	size_t hardlink_length, path_length, linkpath_length;
	size_t uname_length, gname_length;

	char paxbuff[512];
	char ustarbuff[512];
	char ustar_entry_name[256];
	char pax_entry_name[256];
	char gnu_sparse_name[256];
	struct archive_string entry_name;

	ret = ARCHIVE_OK;
	need_extension = 0;
	pax = (struct pax *)a->format_data;

	/* Sanity check. */
	if (archive_entry_pathname(entry_original) == NULL) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			  "Can't record entry in tar file without pathname");
		return (ARCHIVE_FAILED);
	}

	/*
	 * Choose a header encoding.
	 */
	if (pax->opt_binary)
		sconv = NULL;/* Binary mode. */
	else {
		/* Header encoding is UTF-8. */
		if (pax->sconv_utf8 == NULL) {
			/* Initialize the string conversion object
			 * we must need */
			pax->sconv_utf8 = archive_string_conversion_to_charset(
			    &(a->archive), "UTF-8", 1);
			if (pax->sconv_utf8 == NULL)
				/* Couldn't allocate memory */
				return (ARCHIVE_FAILED);
		}
		sconv = pax->sconv_utf8;
	}

	r = get_entry_hardlink(a, entry_original, &hardlink,
	    &hardlink_length, sconv);
	if (r == ARCHIVE_FATAL)
		return (r);
	else if (r != ARCHIVE_OK) {
		r = get_entry_hardlink(a, entry_original, &hardlink,
		    &hardlink_length, NULL);
		if (r == ARCHIVE_FATAL)
			return (r);
		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Can't translate linkname '%s' to %s", hardlink,
		    archive_string_conversion_charset_name(sconv));
		ret = ARCHIVE_WARN;
		sconv = NULL;/* The header charset switches to binary mode. */
	}

	/* Make sure this is a type of entry that we can handle here */
	if (hardlink == NULL) {
		switch (archive_entry_filetype(entry_original)) {
		case AE_IFBLK:
		case AE_IFCHR:
		case AE_IFIFO:
		case AE_IFLNK:
		case AE_IFREG:
			break;
		case AE_IFDIR:
		{
			/*
			 * Ensure a trailing '/'.  Modify the original
			 * entry so the client sees the change.
			 */
#if defined(_WIN32) && !defined(__CYGWIN__)
			const wchar_t *wp;

			wp = archive_entry_pathname_w(entry_original);
			if (wp != NULL && wp[wcslen(wp) -1] != L'/') {
				struct archive_wstring ws;

				archive_string_init(&ws);
				path_length = wcslen(wp);
				if (archive_wstring_ensure(&ws,
				    path_length + 2) == NULL) {
					archive_set_error(&a->archive, ENOMEM,
					    "Can't allocate pax data");
					archive_wstring_free(&ws);
					return(ARCHIVE_FATAL);
				}
				/* Should we keep '\' ? */
				if (wp[path_length -1] == L'\\')
					path_length--;
				archive_wstrncpy(&ws, wp, path_length);
				archive_wstrappend_wchar(&ws, L'/');
				archive_entry_copy_pathname_w(
				    entry_original, ws.s);
				archive_wstring_free(&ws);
				p = NULL;
			} else
#endif
				p = archive_entry_pathname(entry_original);
			/*
			 * On Windows, this is a backup operation just in
			 * case getting WCS failed. On POSIX, this is a
			 * normal operation.
			 */
			if (p != NULL && p[0] != '\0' && p[strlen(p) - 1] != '/') {
				struct archive_string as;

				archive_string_init(&as);
				path_length = strlen(p);
				if (archive_string_ensure(&as,
				    path_length + 2) == NULL) {
					archive_set_error(&a->archive, ENOMEM,
					    "Can't allocate pax data");
					archive_string_free(&as);
					return(ARCHIVE_FATAL);
				}
#if defined(_WIN32) && !defined(__CYGWIN__)
				/* NOTE: This might break the pathname
				 * if the current code page is CP932 and
				 * the pathname includes a character '\'
				 * as a part of its multibyte pathname. */
				if (p[strlen(p) -1] == '\\')
					path_length--;
				else
#endif
				archive_strncpy(&as, p, path_length);
				archive_strappend_char(&as, '/');
				archive_entry_copy_pathname(
				    entry_original, as.s);
				archive_string_free(&as);
			}
			break;
		}
		case AE_IFSOCK:
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "tar format cannot archive socket");
			return (ARCHIVE_FAILED);
		default:
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "tar format cannot archive this (type=0%lo)",
			    (unsigned long)
			    archive_entry_filetype(entry_original));
			return (ARCHIVE_FAILED);
		}
	}

	/*
	 * If Mac OS metadata blob is here, recurse to write that
	 * as a separate entry.  This is really a pretty poor design:
	 * In particular, it doubles the overhead for long filenames.
	 * TODO: Help Apple folks design something better and figure
	 * out how to transition from this legacy format.
	 *
	 * Note that this code is present on every platform; clients
	 * on non-Mac are unlikely to ever provide this data, but
	 * applications that copy entries from one archive to another
	 * should not lose data just because the local filesystem
	 * can't store it.
	 */
	mac_metadata =
	    archive_entry_mac_metadata(entry_original, &mac_metadata_size);
	if (mac_metadata != NULL) {
		const char *oname;
		char *name, *bname;
		size_t name_length;
		struct archive_entry *extra = archive_entry_new2(&a->archive);

		oname = archive_entry_pathname(entry_original);
		name_length = strlen(oname);
		name = malloc(name_length + 3);
		if (name == NULL || extra == NULL) {
			/* XXX error message */
			archive_entry_free(extra);
			free(name);
			return (ARCHIVE_FAILED);
		}
		strcpy(name, oname);
		/* Find last '/'; strip trailing '/' characters */
		bname = strrchr(name, '/');
		while (bname != NULL && bname[1] == '\0') {
			*bname = '\0';
			bname = strrchr(name, '/');
		}
		if (bname == NULL) {
			memmove(name + 2, name, name_length + 1);
			memmove(name, "._", 2);
		} else {
			bname += 1;
			memmove(bname + 2, bname, strlen(bname) + 1);
			memmove(bname, "._", 2);
		}
		archive_entry_copy_pathname(extra, name);
		free(name);

		archive_entry_set_size(extra, mac_metadata_size);
		archive_entry_set_filetype(extra, AE_IFREG);
		archive_entry_set_perm(extra,
		    archive_entry_perm(entry_original));
		archive_entry_set_mtime(extra,
		    archive_entry_mtime(entry_original),
		    archive_entry_mtime_nsec(entry_original));
		archive_entry_set_gid(extra,
		    archive_entry_gid(entry_original));
		archive_entry_set_gname(extra,
		    archive_entry_gname(entry_original));
		archive_entry_set_uid(extra,
		    archive_entry_uid(entry_original));
		archive_entry_set_uname(extra,
		    archive_entry_uname(entry_original));

		/* Recurse to write the special copyfile entry. */
		r = archive_write_pax_header(a, extra);
		archive_entry_free(extra);
		if (r < ARCHIVE_WARN)
			return (r);
		if (r < ret)
			ret = r;
		r = (int)archive_write_pax_data(a, mac_metadata,
		    mac_metadata_size);
		if (r < ARCHIVE_WARN)
			return (r);
		if (r < ret)
			ret = r;
		r = archive_write_pax_finish_entry(a);
		if (r < ARCHIVE_WARN)
			return (r);
		if (r < ret)
			ret = r;
	}

	/* Copy entry so we can modify it as needed. */
#if defined(_WIN32) && !defined(__CYGWIN__)
	/* Make sure the path separators in pathname, hardlink and symlink
	 * are all slash '/', not the Windows path separator '\'. */
	entry_main = __la_win_entry_in_posix_pathseparator(entry_original);
	if (entry_main == entry_original)
		entry_main = archive_entry_clone(entry_original);
#else
	entry_main = archive_entry_clone(entry_original);
#endif
	if (entry_main == NULL) {
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate pax data");
		return(ARCHIVE_FATAL);
	}
	archive_string_empty(&(pax->pax_header)); /* Blank our work area. */
	archive_string_empty(&(pax->sparse_map));
	sparse_total = 0;
	sparse_list_clear(pax);

	if (hardlink == NULL &&
	    archive_entry_filetype(entry_main) == AE_IFREG)
		sparse_count = archive_entry_sparse_reset(entry_main);
	else
		sparse_count = 0;
	if (sparse_count) {
		int64_t offset, length, last_offset = 0;
		/* Get the last entry of sparse block. */
		while (archive_entry_sparse_next(
		    entry_main, &offset, &length) == ARCHIVE_OK)
			last_offset = offset + length;

		/* If the last sparse block does not reach the end of file,
		 * We have to add a empty sparse block as the last entry to
		 * manage storing file data. */
		if (last_offset < archive_entry_size(entry_main))
			archive_entry_sparse_add_entry(entry_main,
			    archive_entry_size(entry_main), 0);
		sparse_count = archive_entry_sparse_reset(entry_main);
	}

	/*
	 * First, check the name fields and see if any of them
	 * require binary coding.  If any of them does, then all of
	 * them do.
	 */
	r = get_entry_pathname(a, entry_main, &path, &path_length, sconv);
	if (r == ARCHIVE_FATAL)
		return (r);
	else if (r != ARCHIVE_OK) {
		r = get_entry_pathname(a, entry_main, &path,
		    &path_length, NULL);
		if (r == ARCHIVE_FATAL)
			return (r);
		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Can't translate pathname '%s' to %s", path,
		    archive_string_conversion_charset_name(sconv));
		ret = ARCHIVE_WARN;
		sconv = NULL;/* The header charset switches to binary mode. */
	}
	r = get_entry_uname(a, entry_main, &uname, &uname_length, sconv);
	if (r == ARCHIVE_FATAL)
		return (r);
	else if (r != ARCHIVE_OK) {
		r = get_entry_uname(a, entry_main, &uname, &uname_length, NULL);
		if (r == ARCHIVE_FATAL)
			return (r);
		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Can't translate uname '%s' to %s", uname,
		    archive_string_conversion_charset_name(sconv));
		ret = ARCHIVE_WARN;
		sconv = NULL;/* The header charset switches to binary mode. */
	}
	r = get_entry_gname(a, entry_main, &gname, &gname_length, sconv);
	if (r == ARCHIVE_FATAL)
		return (r);
	else if (r != ARCHIVE_OK) {
		r = get_entry_gname(a, entry_main, &gname, &gname_length, NULL);
		if (r == ARCHIVE_FATAL)
			return (r);
		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Can't translate gname '%s' to %s", gname,
		    archive_string_conversion_charset_name(sconv));
		ret = ARCHIVE_WARN;
		sconv = NULL;/* The header charset switches to binary mode. */
	}
	linkpath = hardlink;
	linkpath_length = hardlink_length;
	if (linkpath == NULL) {
		r = get_entry_symlink(a, entry_main, &linkpath,
		    &linkpath_length, sconv);
		if (r == ARCHIVE_FATAL)
			return (r);
		else if (r != ARCHIVE_OK) {
			r = get_entry_symlink(a, entry_main, &linkpath,
			    &linkpath_length, NULL);
			if (r == ARCHIVE_FATAL)
				return (r);
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "Can't translate linkname '%s' to %s", linkpath,
			    archive_string_conversion_charset_name(sconv));
			ret = ARCHIVE_WARN;
			sconv = NULL;
		}
	}

	/* If any string conversions failed, get all attributes
	 * in binary-mode. */
	if (sconv == NULL && !pax->opt_binary) {
		if (hardlink != NULL) {
			r = get_entry_hardlink(a, entry_main, &hardlink,
			    &hardlink_length, NULL);
			if (r == ARCHIVE_FATAL)
				return (r);
			linkpath = hardlink;
			linkpath_length = hardlink_length;
		}
		r = get_entry_pathname(a, entry_main, &path,
		    &path_length, NULL);
		if (r == ARCHIVE_FATAL)
			return (r);
		r = get_entry_uname(a, entry_main, &uname, &uname_length, NULL);
		if (r == ARCHIVE_FATAL)
			return (r);
		r = get_entry_gname(a, entry_main, &gname, &gname_length, NULL);
		if (r == ARCHIVE_FATAL)
			return (r);
	}

	/* Store the header encoding first, to be nice to readers. */
	if (sconv == NULL)
		add_pax_attr(&(pax->pax_header), "hdrcharset", "BINARY");


	/*
	 * If name is too long, or has non-ASCII characters, add
	 * 'path' to pax extended attrs.  (Note that an unconvertible
	 * name must have non-ASCII characters.)
	 */
	if (has_non_ASCII(path)) {
		/* We have non-ASCII characters. */
		add_pax_attr(&(pax->pax_header), "path", path);
		archive_entry_set_pathname(entry_main,
		    build_ustar_entry_name(ustar_entry_name,
			path, path_length, NULL));
		need_extension = 1;
	} else {
		/* We have an all-ASCII path; we'd like to just store
		 * it in the ustar header if it will fit.  Yes, this
		 * duplicates some of the logic in
		 * archive_write_set_format_ustar.c
		 */
		if (path_length <= 100) {
			/* Fits in the old 100-char tar name field. */
		} else {
			/* Find largest suffix that will fit. */
			/* Note: strlen() > 100, so strlen() - 100 - 1 >= 0 */
			suffix = strchr(path + path_length - 100 - 1, '/');
			/* Don't attempt an empty prefix. */
			if (suffix == path)
				suffix = strchr(suffix + 1, '/');
			/* We can put it in the ustar header if it's
			 * all ASCII and it's either <= 100 characters
			 * or can be split at a '/' into a prefix <=
			 * 155 chars and a suffix <= 100 chars.  (Note
			 * the strchr() above will return NULL exactly
			 * when the path can't be split.)
			 */
			if (suffix == NULL       /* Suffix > 100 chars. */
			    || suffix[1] == '\0'    /* empty suffix */
			    || suffix - path > 155)  /* Prefix > 155 chars */
			{
				add_pax_attr(&(pax->pax_header), "path", path);
				archive_entry_set_pathname(entry_main,
				    build_ustar_entry_name(ustar_entry_name,
					path, path_length, NULL));
				need_extension = 1;
			}
		}
	}

	if (linkpath != NULL) {
		/* If link name is too long or has non-ASCII characters, add
		 * 'linkpath' to pax extended attrs. */
		if (linkpath_length > 100 || has_non_ASCII(linkpath)) {
			add_pax_attr(&(pax->pax_header), "linkpath", linkpath);
			if (linkpath_length > 100) {
				if (hardlink != NULL)
					archive_entry_set_hardlink(entry_main,
					    "././@LongHardLink");
				else
					archive_entry_set_symlink(entry_main,
					    "././@LongSymLink");
			}
			need_extension = 1;
		}
	}
	/* Save a pathname since it will be renamed if `entry_main` has
	 * sparse blocks. */
	archive_string_init(&entry_name);
	archive_strcpy(&entry_name, archive_entry_pathname(entry_main));

	/* If file size is too large, add 'size' to pax extended attrs. */
	if (archive_entry_size(entry_main) >= (((int64_t)1) << 33)) {
		add_pax_attr_int(&(pax->pax_header), "size",
		    archive_entry_size(entry_main));
		need_extension = 1;
	}

	/* If numeric GID is too large, add 'gid' to pax extended attrs. */
	if ((unsigned int)archive_entry_gid(entry_main) >= (1 << 18)) {
		add_pax_attr_int(&(pax->pax_header), "gid",
		    archive_entry_gid(entry_main));
		need_extension = 1;
	}

	/* If group name is too large or has non-ASCII characters, add
	 * 'gname' to pax extended attrs. */
	if (gname != NULL) {
		if (gname_length > 31 || has_non_ASCII(gname)) {
			add_pax_attr(&(pax->pax_header), "gname", gname);
			need_extension = 1;
		}
	}

	/* If numeric UID is too large, add 'uid' to pax extended attrs. */
	if ((unsigned int)archive_entry_uid(entry_main) >= (1 << 18)) {
		add_pax_attr_int(&(pax->pax_header), "uid",
		    archive_entry_uid(entry_main));
		need_extension = 1;
	}

	/* Add 'uname' to pax extended attrs if necessary. */
	if (uname != NULL) {
		if (uname_length > 31 || has_non_ASCII(uname)) {
			add_pax_attr(&(pax->pax_header), "uname", uname);
			need_extension = 1;
		}
	}

	/*
	 * POSIX/SUSv3 doesn't provide a standard key for large device
	 * numbers.  I use the same keys here that Joerg Schilling
	 * used for 'star.'  (Which, somewhat confusingly, are called
	 * "devXXX" even though they code "rdev" values.)  No doubt,
	 * other implementations use other keys.  Note that there's no
	 * reason we can't write the same information into a number of
	 * different keys.
	 *
	 * Of course, this is only needed for block or char device entries.
	 */
	if (archive_entry_filetype(entry_main) == AE_IFBLK
	    || archive_entry_filetype(entry_main) == AE_IFCHR) {
		/*
		 * If rdevmajor is too large, add 'SCHILY.devmajor' to
		 * extended attributes.
		 */
		int rdevmajor, rdevminor;
		rdevmajor = archive_entry_rdevmajor(entry_main);
		rdevminor = archive_entry_rdevminor(entry_main);
		if (rdevmajor >= (1 << 18)) {
			add_pax_attr_int(&(pax->pax_header), "SCHILY.devmajor",
			    rdevmajor);
			/*
			 * Non-strict formatting below means we don't
			 * have to truncate here.  Not truncating improves
			 * the chance that some more modern tar archivers
			 * (such as GNU tar 1.13) can restore the full
			 * value even if they don't understand the pax
			 * extended attributes.  See my rant below about
			 * file size fields for additional details.
			 */
			/* archive_entry_set_rdevmajor(entry_main,
			   rdevmajor & ((1 << 18) - 1)); */
			need_extension = 1;
		}

		/*
		 * If devminor is too large, add 'SCHILY.devminor' to
		 * extended attributes.
		 */
		if (rdevminor >= (1 << 18)) {
			add_pax_attr_int(&(pax->pax_header), "SCHILY.devminor",
			    rdevminor);
			/* Truncation is not necessary here, either. */
			/* archive_entry_set_rdevminor(entry_main,
			   rdevminor & ((1 << 18) - 1)); */
			need_extension = 1;
		}
	}

	/*
	 * Technically, the mtime field in the ustar header can
	 * support 33 bits, but many platforms use signed 32-bit time
	 * values.  The cutoff of 0x7fffffff here is a compromise.
	 * Yes, this check is duplicated just below; this helps to
	 * avoid writing an mtime attribute just to handle a
	 * high-resolution timestamp in "restricted pax" mode.
	 */
	if (!need_extension &&
	    ((archive_entry_mtime(entry_main) < 0)
		|| (archive_entry_mtime(entry_main) >= 0x7fffffff)))
		need_extension = 1;

	/* I use a star-compatible file flag attribute. */
	p = archive_entry_fflags_text(entry_main);
	if (!need_extension && p != NULL  &&  *p != '\0')
		need_extension = 1;

	/* If there are extended attributes, we need an extension */
	if (!need_extension && archive_entry_xattr_count(entry_original) > 0)
		need_extension = 1;

	/* If there are sparse info, we need an extension */
	if (!need_extension && sparse_count > 0)
		need_extension = 1;

	acl_types = archive_entry_acl_types(entry_original);

	/* If there are any ACL entries, we need an extension */
	if (!need_extension && acl_types != 0)
		need_extension = 1;

	/* If the symlink type is defined, we need an extension */
	if (!need_extension && archive_entry_symlink_type(entry_main) > 0)
		need_extension = 1;

	/*
	 * Libarchive used to include these in extended headers for
	 * restricted pax format, but that confused people who
	 * expected ustar-like time semantics.  So now we only include
	 * them in full pax format.
	 */
	if (a->archive.archive_format != ARCHIVE_FORMAT_TAR_PAX_RESTRICTED) {
		if (archive_entry_ctime(entry_main) != 0  ||
		    archive_entry_ctime_nsec(entry_main) != 0)
			add_pax_attr_time(&(pax->pax_header), "ctime",
			    archive_entry_ctime(entry_main),
			    archive_entry_ctime_nsec(entry_main));

		if (archive_entry_atime(entry_main) != 0 ||
		    archive_entry_atime_nsec(entry_main) != 0)
			add_pax_attr_time(&(pax->pax_header), "atime",
			    archive_entry_atime(entry_main),
			    archive_entry_atime_nsec(entry_main));

		/* Store birth/creationtime only if it's earlier than mtime */
		if (archive_entry_birthtime_is_set(entry_main) &&
		    archive_entry_birthtime(entry_main)
		    < archive_entry_mtime(entry_main))
			add_pax_attr_time(&(pax->pax_header),
			    "LIBARCHIVE.creationtime",
			    archive_entry_birthtime(entry_main),
			    archive_entry_birthtime_nsec(entry_main));
	}

	/*
	 * The following items are handled differently in "pax
	 * restricted" format.  In particular, in "pax restricted"
	 * format they won't be added unless need_extension is
	 * already set (we're already generating an extended header, so
	 * may as well include these).
	 */
	if (a->archive.archive_format != ARCHIVE_FORMAT_TAR_PAX_RESTRICTED ||
	    need_extension) {
		if (archive_entry_mtime(entry_main) < 0  ||
		    archive_entry_mtime(entry_main) >= 0x7fffffff  ||
		    archive_entry_mtime_nsec(entry_main) != 0)
			add_pax_attr_time(&(pax->pax_header), "mtime",
			    archive_entry_mtime(entry_main),
			    archive_entry_mtime_nsec(entry_main));

		/* I use a star-compatible file flag attribute. */
		p = archive_entry_fflags_text(entry_main);
		if (p != NULL  &&  *p != '\0')
			add_pax_attr(&(pax->pax_header), "SCHILY.fflags", p);

		/* I use star-compatible ACL attributes. */
		if ((acl_types & ARCHIVE_ENTRY_ACL_TYPE_NFS4) != 0) {
			ret = add_pax_acl(a, entry_original, pax,
			    ARCHIVE_ENTRY_ACL_STYLE_EXTRA_ID |
			    ARCHIVE_ENTRY_ACL_STYLE_SEPARATOR_COMMA |
			    ARCHIVE_ENTRY_ACL_STYLE_COMPACT);
			if (ret == ARCHIVE_FATAL)
				return (ARCHIVE_FATAL);
		}
		if (acl_types & ARCHIVE_ENTRY_ACL_TYPE_ACCESS) {
			ret = add_pax_acl(a, entry_original, pax,
			    ARCHIVE_ENTRY_ACL_TYPE_ACCESS |
			    ARCHIVE_ENTRY_ACL_STYLE_EXTRA_ID |
			    ARCHIVE_ENTRY_ACL_STYLE_SEPARATOR_COMMA);
			if (ret == ARCHIVE_FATAL)
				return (ARCHIVE_FATAL);
		}
		if (acl_types & ARCHIVE_ENTRY_ACL_TYPE_DEFAULT) {
			ret = add_pax_acl(a, entry_original, pax,
			    ARCHIVE_ENTRY_ACL_TYPE_DEFAULT |
			    ARCHIVE_ENTRY_ACL_STYLE_EXTRA_ID |
			    ARCHIVE_ENTRY_ACL_STYLE_SEPARATOR_COMMA);
			if (ret == ARCHIVE_FATAL)
				return (ARCHIVE_FATAL);
		}

		/* We use GNU-tar-compatible sparse attributes. */
		if (sparse_count > 0) {
			int64_t soffset, slength;

			add_pax_attr_int(&(pax->pax_header),
			    "GNU.sparse.major", 1);
			add_pax_attr_int(&(pax->pax_header),
			    "GNU.sparse.minor", 0);
			/*
			 * Make sure to store the original path, since
			 * truncation to ustar limit happened already.
			 */
			add_pax_attr(&(pax->pax_header),
			    "GNU.sparse.name", path);
			add_pax_attr_int(&(pax->pax_header),
			    "GNU.sparse.realsize",
			    archive_entry_size(entry_main));

			/* Rename the file name which will be used for
			 * ustar header to a special name, which GNU
			 * PAX Format 1.0 requires */
			archive_entry_set_pathname(entry_main,
			    build_gnu_sparse_name(gnu_sparse_name,
			        entry_name.s));

			/*
			 * - Make a sparse map, which will precede a file data.
			 * - Get the total size of available data of sparse.
			 */
			archive_string_sprintf(&(pax->sparse_map), "%d\n",
			    sparse_count);
			while (archive_entry_sparse_next(entry_main,
			    &soffset, &slength) == ARCHIVE_OK) {
				archive_string_sprintf(&(pax->sparse_map),
				    "%jd\n%jd\n",
				    (intmax_t)soffset,
				    (intmax_t)slength);
				sparse_total += slength;
				if (sparse_list_add(pax, soffset, slength)
				    != ARCHIVE_OK) {
					archive_set_error(&a->archive,
					    ENOMEM,
					    "Can't allocate memory");
					archive_entry_free(entry_main);
					archive_string_free(&entry_name);
					return (ARCHIVE_FATAL);
				}
			}
		}

		/* Store extended attributes */
		if (archive_write_pax_header_xattrs(a, pax, entry_original)
		    == ARCHIVE_FATAL) {
			archive_entry_free(entry_main);
			archive_string_free(&entry_name);
			return (ARCHIVE_FATAL);
		}

		/* Store extended symlink information */
		if (archive_entry_symlink_type(entry_main) ==
		    AE_SYMLINK_TYPE_FILE) {
			add_pax_attr(&(pax->pax_header),
			    "LIBARCHIVE.symlinktype", "file");
		} else if (archive_entry_symlink_type(entry_main) ==
		    AE_SYMLINK_TYPE_DIRECTORY) {
			add_pax_attr(&(pax->pax_header),
			    "LIBARCHIVE.symlinktype", "dir");
		}
	}

	/* Only regular files have data. */
	if (archive_entry_filetype(entry_main) != AE_IFREG)
		archive_entry_set_size(entry_main, 0);

	/*
	 * Pax-restricted does not store data for hardlinks, in order
	 * to improve compatibility with ustar.
	 */
	if (a->archive.archive_format != ARCHIVE_FORMAT_TAR_PAX_INTERCHANGE &&
	    hardlink != NULL)
		archive_entry_set_size(entry_main, 0);

	/*
	 * XXX Full pax interchange format does permit a hardlink
	 * entry to have data associated with it.  I'm not supporting
	 * that here because the client expects me to tell them whether
	 * or not this format expects data for hardlinks.  If I
	 * don't check here, then every pax archive will end up with
	 * duplicated data for hardlinks.  Someday, there may be
	 * need to select this behavior, in which case the following
	 * will need to be revisited. XXX
	 */
	if (hardlink != NULL)
		archive_entry_set_size(entry_main, 0);

	/* Save a real file size. */
	real_size = archive_entry_size(entry_main);
	/*
	 * Overwrite a file size by the total size of sparse blocks and
	 * the size of sparse map info. That file size is the length of
	 * the data, which we will exactly store into an archive file.
	 */
	if (archive_strlen(&(pax->sparse_map))) {
		size_t mapsize = archive_strlen(&(pax->sparse_map));
		pax->sparse_map_padding = 0x1ff & (-(ssize_t)mapsize);
		archive_entry_set_size(entry_main,
		    mapsize + pax->sparse_map_padding + sparse_total);
	}

	/* Format 'ustar' header for main entry.
	 *
	 * The trouble with file size: If the reader can't understand
	 * the file size, they may not be able to locate the next
	 * entry and the rest of the archive is toast.  Pax-compliant
	 * readers are supposed to ignore the file size in the main
	 * header, so the question becomes how to maximize portability
	 * for readers that don't support pax attribute extensions.
	 * For maximum compatibility, I permit numeric extensions in
	 * the main header so that the file size stored will always be
	 * correct, even if it's in a format that only some
	 * implementations understand.  The technique used here is:
	 *
	 *  a) If possible, follow the standard exactly.  This handles
	 *  files up to 8 gigabytes minus 1.
	 *
	 *  b) If that fails, try octal but omit the field terminator.
	 *  That handles files up to 64 gigabytes minus 1.
	 *
	 *  c) Otherwise, use base-256 extensions.  That handles files
	 *  up to 2^63 in this implementation, with the potential to
	 *  go up to 2^94.  That should hold us for a while. ;-)
	 *
	 * The non-strict formatter uses similar logic for other
	 * numeric fields, though they're less critical.
	 */
	if (__archive_write_format_header_ustar(a, ustarbuff, entry_main, -1, 0,
	    NULL) == ARCHIVE_FATAL)
		return (ARCHIVE_FATAL);

	/* If we built any extended attributes, write that entry first. */
	if (archive_strlen(&(pax->pax_header)) > 0) {
		struct archive_entry *pax_attr_entry;
		time_t s;
		int64_t uid, gid;
		int mode;

		pax_attr_entry = archive_entry_new2(&a->archive);
		p = entry_name.s;
		archive_entry_set_pathname(pax_attr_entry,
		    build_pax_attribute_name(pax_entry_name, p));
		archive_entry_set_size(pax_attr_entry,
		    archive_strlen(&(pax->pax_header)));
		/* Copy uid/gid (but clip to ustar limits). */
		uid = archive_entry_uid(entry_main);
		if (uid >= 1 << 18)
			uid = (1 << 18) - 1;
		archive_entry_set_uid(pax_attr_entry, uid);
		gid = archive_entry_gid(entry_main);
		if (gid >= 1 << 18)
			gid = (1 << 18) - 1;
		archive_entry_set_gid(pax_attr_entry, gid);
		/* Copy mode over (but not setuid/setgid bits) */
		mode = archive_entry_mode(entry_main);
#ifdef S_ISUID
		mode &= ~S_ISUID;
#endif
#ifdef S_ISGID
		mode &= ~S_ISGID;
#endif
#ifdef S_ISVTX
		mode &= ~S_ISVTX;
#endif
		archive_entry_set_mode(pax_attr_entry, mode);

		/* Copy uname/gname. */
		archive_entry_set_uname(pax_attr_entry,
		    archive_entry_uname(entry_main));
		archive_entry_set_gname(pax_attr_entry,
		    archive_entry_gname(entry_main));

		/* Copy mtime, but clip to ustar limits. */
		s = archive_entry_mtime(entry_main);
		if (s < 0) { s = 0; }
		if (s >= 0x7fffffff) { s = 0x7fffffff; }
		archive_entry_set_mtime(pax_attr_entry, s, 0);

		/* Standard ustar doesn't support atime. */
		archive_entry_set_atime(pax_attr_entry, 0, 0);

		/* Standard ustar doesn't support ctime. */
		archive_entry_set_ctime(pax_attr_entry, 0, 0);

		r = __archive_write_format_header_ustar(a, paxbuff,
		    pax_attr_entry, 'x', 1, NULL);

		archive_entry_free(pax_attr_entry);

		/* Note that the 'x' header shouldn't ever fail to format */
		if (r < ARCHIVE_WARN) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "archive_write_pax_header: "
			    "'x' header failed?!  This can't happen.\n");
			return (ARCHIVE_FATAL);
		} else if (r < ret)
			ret = r;
		r = __archive_write_output(a, paxbuff, 512);
		if (r != ARCHIVE_OK) {
			sparse_list_clear(pax);
			pax->entry_bytes_remaining = 0;
			pax->entry_padding = 0;
			return (ARCHIVE_FATAL);
		}

		pax->entry_bytes_remaining = archive_strlen(&(pax->pax_header));
		pax->entry_padding =
		    0x1ff & (-(int64_t)pax->entry_bytes_remaining);

		r = __archive_write_output(a, pax->pax_header.s,
		    archive_strlen(&(pax->pax_header)));
		if (r != ARCHIVE_OK) {
			/* If a write fails, we're pretty much toast. */
			return (ARCHIVE_FATAL);
		}
		/* Pad out the end of the entry. */
		r = __archive_write_nulls(a, (size_t)pax->entry_padding);
		if (r != ARCHIVE_OK) {
			/* If a write fails, we're pretty much toast. */
			return (ARCHIVE_FATAL);
		}
		pax->entry_bytes_remaining = pax->entry_padding = 0;
	}

	/* Write the header for main entry. */
	r = __archive_write_output(a, ustarbuff, 512);
	if (r != ARCHIVE_OK)
		return (r);

	/*
	 * Inform the client of the on-disk size we're using, so
	 * they can avoid unnecessarily writing a body for something
	 * that we're just going to ignore.
	 */
	archive_entry_set_size(entry_original, real_size);
	if (pax->sparse_list == NULL && real_size > 0) {
		/* This is not a sparse file but we handle its data as
		 * a sparse block. */
		sparse_list_add(pax, 0, real_size);
		sparse_total = real_size;
	}
	pax->entry_padding = 0x1ff & (-(int64_t)sparse_total);
	archive_entry_free(entry_main);
	archive_string_free(&entry_name);

	return (ret);
}