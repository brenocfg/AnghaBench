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
typedef  int wchar_t ;
struct v7tar {int init_default_conversion; int entry_padding; scalar_t__ entry_bytes_remaining; struct archive_string_conv* opt_sconv; struct archive_string_conv* sconv_default; } ;
struct archive_wstring {int /*<<< orphan*/  s; } ;
struct archive_write {int /*<<< orphan*/  archive; scalar_t__ format_data; } ;
struct archive_string_conv {int dummy; } ;
struct archive_string {int /*<<< orphan*/  s; } ;
struct archive_entry {int dummy; } ;
typedef  int int64_t ;

/* Variables and functions */
 scalar_t__ AE_IFDIR ; 
 scalar_t__ AE_IFREG ; 
 int /*<<< orphan*/  ARCHIVE_ERRNO_MISC ; 
 int ARCHIVE_FAILED ; 
 int ARCHIVE_FATAL ; 
 int ARCHIVE_WARN ; 
 int /*<<< orphan*/  ENOMEM ; 
 int __archive_write_output (struct archive_write*,char*,int) ; 
 struct archive_entry* __la_win_entry_in_posix_pathseparator (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_copy_pathname (struct archive_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_copy_pathname_w (struct archive_entry*,int /*<<< orphan*/ ) ; 
 scalar_t__ archive_entry_filetype (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_free (struct archive_entry*) ; 
 int /*<<< orphan*/ * archive_entry_hardlink (struct archive_entry*) ; 
 char* archive_entry_pathname (struct archive_entry*) ; 
 int* archive_entry_pathname_w (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_set_size (struct archive_entry*,int /*<<< orphan*/ ) ; 
 scalar_t__ archive_entry_size (struct archive_entry*) ; 
 int /*<<< orphan*/ * archive_entry_symlink (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  archive_strappend_char (struct archive_wstring*,char) ; 
 struct archive_string_conv* archive_string_default_conversion_for_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * archive_string_ensure (struct archive_wstring*,size_t) ; 
 int /*<<< orphan*/  archive_string_free (struct archive_wstring*) ; 
 int /*<<< orphan*/  archive_string_init (struct archive_wstring*) ; 
 int /*<<< orphan*/  archive_strncpy (struct archive_wstring*,char const*,size_t) ; 
 int /*<<< orphan*/  archive_wstrappend_wchar (struct archive_wstring*,int) ; 
 int /*<<< orphan*/ * archive_wstring_ensure (struct archive_wstring*,size_t) ; 
 int /*<<< orphan*/  archive_wstring_free (struct archive_wstring*) ; 
 int /*<<< orphan*/  archive_wstrncpy (struct archive_wstring*,int const*,size_t) ; 
 int format_header_v7tar (struct archive_write*,char*,struct archive_entry*,int,struct archive_string_conv*) ; 
 int strlen (char const*) ; 
 int wcslen (int const*) ; 

__attribute__((used)) static int
archive_write_v7tar_header(struct archive_write *a, struct archive_entry *entry)
{
	char buff[512];
	int ret, ret2;
	struct v7tar *v7tar;
	struct archive_entry *entry_main;
	struct archive_string_conv *sconv;

	v7tar = (struct v7tar *)a->format_data;

	/* Setup default string conversion. */
	if (v7tar->opt_sconv == NULL) {
		if (!v7tar->init_default_conversion) {
			v7tar->sconv_default =
			    archive_string_default_conversion_for_write(
				&(a->archive));
			v7tar->init_default_conversion = 1;
		}
		sconv = v7tar->sconv_default;
	} else
		sconv = v7tar->opt_sconv;

	/* Sanity check. */
	if (archive_entry_pathname(entry) == NULL) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Can't record entry in tar file without pathname");
		return (ARCHIVE_FAILED);
	}

	/* Only regular files (not hardlinks) have data. */
	if (archive_entry_hardlink(entry) != NULL ||
	    archive_entry_symlink(entry) != NULL ||
	    !(archive_entry_filetype(entry) == AE_IFREG))
		archive_entry_set_size(entry, 0);

	if (AE_IFDIR == archive_entry_filetype(entry)) {
		const char *p;
		size_t path_length;
		/*
		 * Ensure a trailing '/'.  Modify the entry so
		 * the client sees the change.
		 */
#if defined(_WIN32) && !defined(__CYGWIN__)
		const wchar_t *wp;

		wp = archive_entry_pathname_w(entry);
		if (wp != NULL && wp[wcslen(wp) -1] != L'/') {
			struct archive_wstring ws;

			archive_string_init(&ws);
			path_length = wcslen(wp);
			if (archive_wstring_ensure(&ws,
			    path_length + 2) == NULL) {
				archive_set_error(&a->archive, ENOMEM,
				    "Can't allocate v7tar data");
				archive_wstring_free(&ws);
				return(ARCHIVE_FATAL);
			}
			/* Should we keep '\' ? */
			if (wp[path_length -1] == L'\\')
				path_length--;
			archive_wstrncpy(&ws, wp, path_length);
			archive_wstrappend_wchar(&ws, L'/');
			archive_entry_copy_pathname_w(entry, ws.s);
			archive_wstring_free(&ws);
			p = NULL;
		} else
#endif
			p = archive_entry_pathname(entry);
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
				    "Can't allocate v7tar data");
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
			archive_entry_copy_pathname(entry, as.s);
			archive_string_free(&as);
		}
	}

#if defined(_WIN32) && !defined(__CYGWIN__)
	/* Make sure the path separators in pathname, hardlink and symlink
	 * are all slash '/', not the Windows path separator '\'. */
	entry_main = __la_win_entry_in_posix_pathseparator(entry);
	if (entry_main == NULL) {
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate v7tar data");
		return(ARCHIVE_FATAL);
	}
	if (entry != entry_main)
		entry = entry_main;
	else
		entry_main = NULL;
#else
	entry_main = NULL;
#endif
	ret = format_header_v7tar(a, buff, entry, 1, sconv);
	if (ret < ARCHIVE_WARN) {
		archive_entry_free(entry_main);
		return (ret);
	}
	ret2 = __archive_write_output(a, buff, 512);
	if (ret2 < ARCHIVE_WARN) {
		archive_entry_free(entry_main);
		return (ret2);
	}
	if (ret2 < ret)
		ret = ret2;

	v7tar->entry_bytes_remaining = archive_entry_size(entry);
	v7tar->entry_padding = 0x1ff & (-(int64_t)v7tar->entry_bytes_remaining);
	archive_entry_free(entry_main);
	return (ret);
}