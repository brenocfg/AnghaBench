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
struct tar {int /*<<< orphan*/ * sconv_acl; } ;
struct archive_read {int /*<<< orphan*/  archive; } ;
struct archive_entry {int dummy; } ;

/* Variables and functions */
#define  ARCHIVE_ENTRY_ACL_TYPE_ACCESS 130 
#define  ARCHIVE_ENTRY_ACL_TYPE_DEFAULT 129 
#define  ARCHIVE_ENTRY_ACL_TYPE_NFS4 128 
 int /*<<< orphan*/  ARCHIVE_ERRNO_MISC ; 
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  ENOMEM ; 
 int archive_acl_from_text_l (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  archive_entry_acl (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * archive_string_conversion_from_charset (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int
pax_attribute_acl(struct archive_read *a, struct tar *tar,
    struct archive_entry *entry, const char *value, int type)
{
	int r;
	const char* errstr;

	switch (type) {
	case ARCHIVE_ENTRY_ACL_TYPE_ACCESS:
		errstr = "SCHILY.acl.access";
		break;
	case ARCHIVE_ENTRY_ACL_TYPE_DEFAULT:
		errstr = "SCHILY.acl.default";
		break;
	case ARCHIVE_ENTRY_ACL_TYPE_NFS4:
		errstr = "SCHILY.acl.ace";
		break;
	default:
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Unknown ACL type: %d", type);
		return(ARCHIVE_FATAL);
	}

	if (tar->sconv_acl == NULL) {
		tar->sconv_acl =
		    archive_string_conversion_from_charset(
			&(a->archive), "UTF-8", 1);
		if (tar->sconv_acl == NULL)
			return (ARCHIVE_FATAL);
	}

	r = archive_acl_from_text_l(archive_entry_acl(entry), value, type,
	    tar->sconv_acl);
	if (r != ARCHIVE_OK) {
		if (r == ARCHIVE_FATAL) {
			archive_set_error(&a->archive, ENOMEM,
			    "%s %s", "Can't allocate memory for ",
			    errstr);
			return (r);
		}
		archive_set_error(&a->archive,
		    ARCHIVE_ERRNO_MISC, "%s %s", "Parse error: ", errstr);
	}
	return (r);
}