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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  uid_t ;
struct archive_string_conv {int dummy; } ;
struct archive_acl_entry {int type; int tag; int id; int /*<<< orphan*/  name; struct archive_acl_entry* next; } ;
struct archive_acl {struct archive_acl_entry* acl_head; } ;
struct archive {int dummy; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
#define  ARCHIVE_ENTRY_ACL_EVERYONE 134 
#define  ARCHIVE_ENTRY_ACL_GROUP 133 
#define  ARCHIVE_ENTRY_ACL_GROUP_OBJ 132 
#define  ARCHIVE_ENTRY_ACL_MASK 131 
#define  ARCHIVE_ENTRY_ACL_OTHER 130 
 int ARCHIVE_ENTRY_ACL_STYLE_EXTRA_ID ; 
 int ARCHIVE_ENTRY_ACL_STYLE_SOLARIS ; 
 int ARCHIVE_ENTRY_ACL_TYPE_ACCESS ; 
 int ARCHIVE_ENTRY_ACL_TYPE_DEFAULT ; 
 int ARCHIVE_ENTRY_ACL_TYPE_DENY ; 
 int ARCHIVE_ENTRY_ACL_TYPE_NFS4 ; 
 int ARCHIVE_ENTRY_ACL_TYPE_POSIX1E ; 
#define  ARCHIVE_ENTRY_ACL_USER 129 
#define  ARCHIVE_ENTRY_ACL_USER_OBJ 128 
 scalar_t__ ENOMEM ; 
 int archive_mstring_get_mbs_l (int /*<<< orphan*/ *,char const**,size_t*,struct archive_string_conv*) ; 
 int archive_mstring_get_wcs (struct archive*,int /*<<< orphan*/ *,int /*<<< orphan*/  const**) ; 
 scalar_t__ errno ; 
 scalar_t__ wcslen (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static ssize_t
archive_acl_text_len(struct archive_acl *acl, int want_type, int flags,
    int wide, struct archive *a, struct archive_string_conv *sc) {
	struct archive_acl_entry *ap;
	const char *name;
	const wchar_t *wname;
	int count, idlen, tmp, r;
	ssize_t length;
	size_t len;

	count = 0;
	length = 0;
	for (ap = acl->acl_head; ap != NULL; ap = ap->next) {
		if ((ap->type & want_type) == 0)
			continue;
		/*
		 * Filemode-mapping ACL entries are stored exclusively in
		 * ap->mode so they should not be in the list
		 */
		if ((ap->type == ARCHIVE_ENTRY_ACL_TYPE_ACCESS)
		    && (ap->tag == ARCHIVE_ENTRY_ACL_USER_OBJ
		    || ap->tag == ARCHIVE_ENTRY_ACL_GROUP_OBJ
		    || ap->tag == ARCHIVE_ENTRY_ACL_OTHER))
			continue;
		count++;
		if ((want_type & ARCHIVE_ENTRY_ACL_TYPE_DEFAULT) != 0
		    && (ap->type & ARCHIVE_ENTRY_ACL_TYPE_DEFAULT) != 0)
			length += 8; /* "default:" */
		switch (ap->tag) {
		case ARCHIVE_ENTRY_ACL_USER_OBJ:
			if (want_type == ARCHIVE_ENTRY_ACL_TYPE_NFS4) {
				length += 6; /* "owner@" */
				break;
			}
			/* FALLTHROUGH */
		case ARCHIVE_ENTRY_ACL_USER:
		case ARCHIVE_ENTRY_ACL_MASK:
			length += 4; /* "user", "mask" */
			break;
		case ARCHIVE_ENTRY_ACL_GROUP_OBJ:
			if (want_type == ARCHIVE_ENTRY_ACL_TYPE_NFS4) {
				length += 6; /* "group@" */
				break;
			}
			/* FALLTHROUGH */
		case ARCHIVE_ENTRY_ACL_GROUP:
		case ARCHIVE_ENTRY_ACL_OTHER:
			length += 5; /* "group", "other" */
			break;
		case ARCHIVE_ENTRY_ACL_EVERYONE:
			length += 9; /* "everyone@" */
			break;
		}
		length += 1; /* colon after tag */
		if (ap->tag == ARCHIVE_ENTRY_ACL_USER ||
		    ap->tag == ARCHIVE_ENTRY_ACL_GROUP) {
			if (wide) {
				r = archive_mstring_get_wcs(a, &ap->name,
				    &wname);
				if (r == 0 && wname != NULL)
					length += wcslen(wname);
				else if (r < 0 && errno == ENOMEM)
					return (0);
				else
					length += sizeof(uid_t) * 3 + 1;
			} else {
				r = archive_mstring_get_mbs_l(&ap->name, &name,
				    &len, sc);
				if (r != 0)
					return (0);
				if (len > 0 && name != NULL)
					length += len;
				else
					length += sizeof(uid_t) * 3 + 1;
			}
			length += 1; /* colon after user or group name */
		} else if (want_type != ARCHIVE_ENTRY_ACL_TYPE_NFS4)
			length += 1; /* 2nd colon empty user,group or other */

		if (((flags & ARCHIVE_ENTRY_ACL_STYLE_SOLARIS) != 0)
		    && ((want_type & ARCHIVE_ENTRY_ACL_TYPE_POSIX1E) != 0)
		    && (ap->tag == ARCHIVE_ENTRY_ACL_OTHER
		    || ap->tag == ARCHIVE_ENTRY_ACL_MASK)) {
			/* Solaris has no colon after other: and mask: */
			length = length - 1;
		}

		if (want_type == ARCHIVE_ENTRY_ACL_TYPE_NFS4) {
			/* rwxpdDaARWcCos:fdinSFI:deny */
			length += 27;
			if ((ap->type & ARCHIVE_ENTRY_ACL_TYPE_DENY) == 0)
				length += 1; /* allow, alarm, audit */
		} else
			length += 3; /* rwx */

		if ((ap->tag == ARCHIVE_ENTRY_ACL_USER ||
		    ap->tag == ARCHIVE_ENTRY_ACL_GROUP) &&
		    (flags & ARCHIVE_ENTRY_ACL_STYLE_EXTRA_ID) != 0) {
			length += 1; /* colon */
			/* ID digit count */
			idlen = 1;
			tmp = ap->id;
			while (tmp > 9) {
				tmp = tmp / 10;
				idlen++;
			}
			length += idlen;
		}
		length ++; /* entry separator */
	}

	/* Add filemode-mapping access entries to the length */
	if ((want_type & ARCHIVE_ENTRY_ACL_TYPE_ACCESS) != 0) {
		if ((flags & ARCHIVE_ENTRY_ACL_STYLE_SOLARIS) != 0) {
			/* "user::rwx\ngroup::rwx\nother:rwx\n" */
			length += 31;
		} else {
			/* "user::rwx\ngroup::rwx\nother::rwx\n" */
			length += 32;
		}
	} else if (count == 0)
		return (0);

	/* The terminating character is included in count */
	return (length);
}