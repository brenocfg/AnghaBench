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
struct pax {int /*<<< orphan*/  pax_header; int /*<<< orphan*/  sconv_utf8; } ;
struct archive_write {int /*<<< orphan*/  archive; } ;
struct archive_entry {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_ENTRY_ACL_TYPE_ACCESS ; 
 int ARCHIVE_ENTRY_ACL_TYPE_DEFAULT ; 
 int ARCHIVE_ENTRY_ACL_TYPE_NFS4 ; 
 int /*<<< orphan*/  ARCHIVE_ERRNO_FILE_FORMAT ; 
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int ARCHIVE_WARN ; 
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  add_pax_attr (int /*<<< orphan*/ *,char const*,char*) ; 
 char* archive_entry_acl_to_text_l (struct archive_entry*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int archive_entry_acl_types (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,scalar_t__,char*,char*,char const*,...) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (char*) ; 

__attribute__((used)) static int
add_pax_acl(struct archive_write *a,
    struct archive_entry *entry, struct pax *pax, int flags)
{
	char *p;
	const char *attr;
	int acl_types;

	acl_types = archive_entry_acl_types(entry);

	if ((acl_types & ARCHIVE_ENTRY_ACL_TYPE_NFS4) != 0)
		attr = "SCHILY.acl.ace";
	else if ((flags & ARCHIVE_ENTRY_ACL_TYPE_ACCESS) != 0)
		attr = "SCHILY.acl.access";
	else if ((flags & ARCHIVE_ENTRY_ACL_TYPE_DEFAULT) != 0)
		attr = "SCHILY.acl.default";
	else
		return (ARCHIVE_FATAL);

	p = archive_entry_acl_to_text_l(entry, NULL, flags, pax->sconv_utf8);
	if (p == NULL) {
		if (errno == ENOMEM) {
			archive_set_error(&a->archive, ENOMEM, "%s %s",
			    "Can't allocate memory for ", attr);
			return (ARCHIVE_FATAL);
		}
		archive_set_error(&a->archive,
		    ARCHIVE_ERRNO_FILE_FORMAT, "%s %s %s",
		    "Can't translate ", attr, " to UTF-8");
		return(ARCHIVE_WARN);
	}

	if (*p != '\0') {
		add_pax_attr(&(pax->pax_header),
		    attr, p);
	}
	free(p);
	return(ARCHIVE_OK);
}