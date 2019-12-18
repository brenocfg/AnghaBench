#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  s; } ;
struct TYPE_3__ {char* s; } ;
struct tar {int /*<<< orphan*/ * sconv_acl; TYPE_2__ localname; TYPE_1__ acl_text; } ;
struct archive_read {int /*<<< orphan*/  archive; } ;
struct archive_entry_header_ustar {int /*<<< orphan*/  size; } ;
struct archive_entry {int dummy; } ;
typedef  int int64_t ;

/* Variables and functions */
 int ARCHIVE_ENTRY_ACL_TYPE_ACCESS ; 
 int ARCHIVE_ENTRY_ACL_TYPE_NFS4 ; 
 scalar_t__ ARCHIVE_ERRNO_MISC ; 
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int ARCHIVE_WARN ; 
 scalar_t__ ENOMEM ; 
 int archive_acl_from_text_l (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  archive_entry_acl (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,scalar_t__,char*,...) ; 
 int /*<<< orphan*/ * archive_string_conversion_from_charset (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  archive_strncpy (TYPE_2__*,char*,int) ; 
 scalar_t__ errno ; 
 int read_body_to_string (struct archive_read*,struct tar*,TYPE_1__*,void const*,size_t*) ; 
 scalar_t__ tar_atol (int /*<<< orphan*/ ,int) ; 
 int tar_read_header (struct archive_read*,struct tar*,struct archive_entry*,size_t*) ; 

__attribute__((used)) static int
header_Solaris_ACL(struct archive_read *a, struct tar *tar,
    struct archive_entry *entry, const void *h, size_t *unconsumed)
{
	const struct archive_entry_header_ustar *header;
	size_t size;
	int err, acl_type;
	int64_t type;
	char *acl, *p;

	/*
	 * read_body_to_string adds a NUL terminator, but we need a little
	 * more to make sure that we don't overrun acl_text later.
	 */
	header = (const struct archive_entry_header_ustar *)h;
	size = (size_t)tar_atol(header->size, sizeof(header->size));
	err = read_body_to_string(a, tar, &(tar->acl_text), h, unconsumed);
	if (err != ARCHIVE_OK)
		return (err);

	/* Recursively read next header */
	err = tar_read_header(a, tar, entry, unconsumed);
	if ((err != ARCHIVE_OK) && (err != ARCHIVE_WARN))
		return (err);

	/* TODO: Examine the first characters to see if this
	 * is an AIX ACL descriptor.  We'll likely never support
	 * them, but it would be polite to recognize and warn when
	 * we do see them. */

	/* Leading octal number indicates ACL type and number of entries. */
	p = acl = tar->acl_text.s;
	type = 0;
	while (*p != '\0' && p < acl + size) {
		if (*p < '0' || *p > '7') {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Malformed Solaris ACL attribute (invalid digit)");
			return(ARCHIVE_WARN);
		}
		type <<= 3;
		type += *p - '0';
		if (type > 077777777) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Malformed Solaris ACL attribute (count too large)");
			return (ARCHIVE_WARN);
		}
		p++;
	}
	switch ((int)type & ~0777777) {
	case 01000000:
		/* POSIX.1e ACL */
		acl_type = ARCHIVE_ENTRY_ACL_TYPE_ACCESS;
		break;
	case 03000000:
		/* NFSv4 ACL */
		acl_type = ARCHIVE_ENTRY_ACL_TYPE_NFS4;
		break;
	default:
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Malformed Solaris ACL attribute (unsupported type %o)",
		    (int)type);
		return (ARCHIVE_WARN);
	}
	p++;

	if (p >= acl + size) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Malformed Solaris ACL attribute (body overflow)");
		return(ARCHIVE_WARN);
	}

	/* ACL text is null-terminated; find the end. */
	size -= (p - acl);
	acl = p;

	while (*p != '\0' && p < acl + size)
		p++;

	if (tar->sconv_acl == NULL) {
		tar->sconv_acl = archive_string_conversion_from_charset(
		    &(a->archive), "UTF-8", 1);
		if (tar->sconv_acl == NULL)
			return (ARCHIVE_FATAL);
	}
	archive_strncpy(&(tar->localname), acl, p - acl);
	err = archive_acl_from_text_l(archive_entry_acl(entry),
	    tar->localname.s, acl_type, tar->sconv_acl);
	if (err != ARCHIVE_OK) {
		if (errno == ENOMEM) {
			archive_set_error(&a->archive, ENOMEM,
			    "Can't allocate memory for ACL");
		} else
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Malformed Solaris ACL attribute (unparsable)");
	}
	return (err);
}