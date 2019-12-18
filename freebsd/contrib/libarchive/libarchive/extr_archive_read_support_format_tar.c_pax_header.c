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
struct archive_string {char* s; size_t length; } ;
struct tar {struct archive_string entry_uname; struct archive_string entry_pathname; struct archive_string entry_pathname_override; struct archive_string entry_linkpath; struct archive_string entry_gname; scalar_t__ compat_2x; struct archive_string_conv* opt_sconv; scalar_t__ pax_hdrcharset_binary; } ;
struct archive_string_conv {int dummy; } ;
struct archive_read {int /*<<< orphan*/  archive; } ;
struct archive_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_ERRNO_MISC ; 
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int ARCHIVE_WARN ; 
 int /*<<< orphan*/  SCONV_SET_OPT_UTF8_LIBARCHIVE2X ; 
 int /*<<< orphan*/  archive_entry_copy_gname (struct archive_entry*,char*) ; 
 scalar_t__ archive_entry_copy_gname_l (struct archive_entry*,char*,int /*<<< orphan*/ ,struct archive_string_conv*) ; 
 int /*<<< orphan*/  archive_entry_copy_link (struct archive_entry*,char*) ; 
 scalar_t__ archive_entry_copy_link_l (struct archive_entry*,char*,int /*<<< orphan*/ ,struct archive_string_conv*) ; 
 int /*<<< orphan*/  archive_entry_copy_pathname (struct archive_entry*,char*) ; 
 scalar_t__ archive_entry_copy_pathname_l (struct archive_entry*,char*,int /*<<< orphan*/ ,struct archive_string_conv*) ; 
 int /*<<< orphan*/  archive_entry_copy_uname (struct archive_entry*,char*) ; 
 scalar_t__ archive_entry_copy_uname_l (struct archive_entry*,char*,int /*<<< orphan*/ ,struct archive_string_conv*) ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 struct archive_string_conv* archive_string_conversion_from_charset (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  archive_string_conversion_set_opt (struct archive_string_conv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_string_empty (struct archive_string*) ; 
 int /*<<< orphan*/  archive_strlen (struct archive_string*) ; 
 int err_combine (int,int) ; 
 int pax_attribute (struct archive_read*,struct tar*,struct archive_entry*,char*,char*,size_t) ; 
 int set_conversion_failed_error (struct archive_read*,struct archive_string_conv*,char*) ; 

__attribute__((used)) static int
pax_header(struct archive_read *a, struct tar *tar,
    struct archive_entry *entry, struct archive_string *in_as)
{
	size_t attr_length, l, line_length, value_length;
	char *p;
	char *key, *value;
	struct archive_string *as;
	struct archive_string_conv *sconv;
	int err, err2;
	char *attr = in_as->s;

	attr_length = in_as->length;
	tar->pax_hdrcharset_binary = 0;
	archive_string_empty(&(tar->entry_gname));
	archive_string_empty(&(tar->entry_linkpath));
	archive_string_empty(&(tar->entry_pathname));
	archive_string_empty(&(tar->entry_pathname_override));
	archive_string_empty(&(tar->entry_uname));
	err = ARCHIVE_OK;
	while (attr_length > 0) {
		/* Parse decimal length field at start of line. */
		line_length = 0;
		l = attr_length;
		p = attr; /* Record start of line. */
		while (l>0) {
			if (*p == ' ') {
				p++;
				l--;
				break;
			}
			if (*p < '0' || *p > '9') {
				archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
				    "Ignoring malformed pax extended attributes");
				return (ARCHIVE_WARN);
			}
			line_length *= 10;
			line_length += *p - '0';
			if (line_length > 999999) {
				archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
				    "Rejecting pax extended attribute > 1MB");
				return (ARCHIVE_WARN);
			}
			p++;
			l--;
		}

		/*
		 * Parsed length must be no bigger than available data,
		 * at least 1, and the last character of the line must
		 * be '\n'.
		 */
		if (line_length > attr_length
		    || line_length < 1
		    || attr[line_length - 1] != '\n')
		{
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Ignoring malformed pax extended attribute");
			return (ARCHIVE_WARN);
		}

		/* Null-terminate the line. */
		attr[line_length - 1] = '\0';

		/* Find end of key and null terminate it. */
		key = p;
		if (key[0] == '=')
			return (-1);
		while (*p && *p != '=')
			++p;
		if (*p == '\0') {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Invalid pax extended attributes");
			return (ARCHIVE_WARN);
		}
		*p = '\0';

		value = p + 1;

		/* Some values may be binary data */
		value_length = attr + line_length - 1 - value;

		/* Identify this attribute and set it in the entry. */
		err2 = pax_attribute(a, tar, entry, key, value, value_length);
		if (err2 == ARCHIVE_FATAL)
			return (err2);
		err = err_combine(err, err2);

		/* Skip to next line */
		attr += line_length;
		attr_length -= line_length;
	}

	/*
	 * PAX format uses UTF-8 as default charset for its metadata
	 * unless hdrcharset=BINARY is present in its header.
	 * We apply the charset specified by the hdrcharset option only
	 * when the hdrcharset attribute(in PAX header) is BINARY because
	 * we respect the charset described in PAX header and BINARY also
	 * means that metadata(filename,uname and gname) character-set
	 * is unknown.
	 */
	if (tar->pax_hdrcharset_binary)
		sconv = tar->opt_sconv;
	else {
		sconv = archive_string_conversion_from_charset(
		    &(a->archive), "UTF-8", 1);
		if (sconv == NULL)
			return (ARCHIVE_FATAL);
		if (tar->compat_2x)
			archive_string_conversion_set_opt(sconv,
			    SCONV_SET_OPT_UTF8_LIBARCHIVE2X);
	}

	if (archive_strlen(&(tar->entry_gname)) > 0) {
		if (archive_entry_copy_gname_l(entry, tar->entry_gname.s,
		    archive_strlen(&(tar->entry_gname)), sconv) != 0) {
			err = set_conversion_failed_error(a, sconv, "Gname");
			if (err == ARCHIVE_FATAL)
				return (err);
			/* Use a converted an original name. */
			archive_entry_copy_gname(entry, tar->entry_gname.s);
		}
	}
	if (archive_strlen(&(tar->entry_linkpath)) > 0) {
		if (archive_entry_copy_link_l(entry, tar->entry_linkpath.s,
		    archive_strlen(&(tar->entry_linkpath)), sconv) != 0) {
			err = set_conversion_failed_error(a, sconv, "Linkname");
			if (err == ARCHIVE_FATAL)
				return (err);
			/* Use a converted an original name. */
			archive_entry_copy_link(entry, tar->entry_linkpath.s);
		}
	}
	/*
	 * Some extensions (such as the GNU sparse file extensions)
	 * deliberately store a synthetic name under the regular 'path'
	 * attribute and the real file name under a different attribute.
	 * Since we're supposed to not care about the order, we
	 * have no choice but to store all of the various filenames
	 * we find and figure it all out afterwards.  This is the
	 * figuring out part.
	 */
	as = NULL;
	if (archive_strlen(&(tar->entry_pathname_override)) > 0)
		as = &(tar->entry_pathname_override);
	else if (archive_strlen(&(tar->entry_pathname)) > 0)
		as = &(tar->entry_pathname);
	if (as != NULL) {
		if (archive_entry_copy_pathname_l(entry, as->s,
		    archive_strlen(as), sconv) != 0) {
			err = set_conversion_failed_error(a, sconv, "Pathname");
			if (err == ARCHIVE_FATAL)
				return (err);
			/* Use a converted an original name. */
			archive_entry_copy_pathname(entry, as->s);
		}
	}
	if (archive_strlen(&(tar->entry_uname)) > 0) {
		if (archive_entry_copy_uname_l(entry, tar->entry_uname.s,
		    archive_strlen(&(tar->entry_uname)), sconv) != 0) {
			err = set_conversion_failed_error(a, sconv, "Uname");
			if (err == ARCHIVE_FATAL)
				return (err);
			/* Use a converted an original name. */
			archive_entry_copy_uname(entry, tar->entry_uname.s);
		}
	}
	return (err);
}