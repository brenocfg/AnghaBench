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
typedef  char wchar_t ;
struct TYPE_4__ {int perm; int /*<<< orphan*/  wc; } ;
struct TYPE_3__ {int perm; int /*<<< orphan*/  wc; } ;

/* Variables and functions */
#define  ARCHIVE_ENTRY_ACL_EVERYONE 138 
#define  ARCHIVE_ENTRY_ACL_GROUP 137 
#define  ARCHIVE_ENTRY_ACL_GROUP_OBJ 136 
#define  ARCHIVE_ENTRY_ACL_MASK 135 
#define  ARCHIVE_ENTRY_ACL_OTHER 134 
 int ARCHIVE_ENTRY_ACL_STYLE_COMPACT ; 
 int ARCHIVE_ENTRY_ACL_STYLE_SOLARIS ; 
#define  ARCHIVE_ENTRY_ACL_TYPE_ALARM 133 
#define  ARCHIVE_ENTRY_ACL_TYPE_ALLOW 132 
#define  ARCHIVE_ENTRY_ACL_TYPE_AUDIT 131 
#define  ARCHIVE_ENTRY_ACL_TYPE_DENY 130 
 int ARCHIVE_ENTRY_ACL_TYPE_NFS4 ; 
 int ARCHIVE_ENTRY_ACL_TYPE_POSIX1E ; 
#define  ARCHIVE_ENTRY_ACL_USER 129 
#define  ARCHIVE_ENTRY_ACL_USER_OBJ 128 
 int /*<<< orphan*/  append_id_w (char**,int) ; 
 TYPE_2__* nfsv4_acl_flag_map ; 
 int nfsv4_acl_flag_map_size ; 
 TYPE_1__* nfsv4_acl_perm_map ; 
 int nfsv4_acl_perm_map_size ; 
 int /*<<< orphan*/  wcscpy (char*,char const*) ; 
 int /*<<< orphan*/  wcslen (char*) ; 

__attribute__((used)) static void
append_entry_w(wchar_t **wp, const wchar_t *prefix, int type,
    int tag, int flags, const wchar_t *wname, int perm, int id)
{
	int i;

	if (prefix != NULL) {
		wcscpy(*wp, prefix);
		*wp += wcslen(*wp);
	}
	switch (tag) {
	case ARCHIVE_ENTRY_ACL_USER_OBJ:
		wname = NULL;
		id = -1;
		if ((type & ARCHIVE_ENTRY_ACL_TYPE_NFS4) != 0) {
			wcscpy(*wp, L"owner@");
			break;
		}
		/* FALLTHROUGH */
	case ARCHIVE_ENTRY_ACL_USER:
		wcscpy(*wp, L"user");
		break;
	case ARCHIVE_ENTRY_ACL_GROUP_OBJ:
		wname = NULL;
		id = -1;
		if ((type & ARCHIVE_ENTRY_ACL_TYPE_NFS4) != 0) {
			wcscpy(*wp, L"group@");
			break;
		}
		/* FALLTHROUGH */
	case ARCHIVE_ENTRY_ACL_GROUP:
		wcscpy(*wp, L"group");
		break;
	case ARCHIVE_ENTRY_ACL_MASK:
		wcscpy(*wp, L"mask");
		wname = NULL;
		id = -1;
		break;
	case ARCHIVE_ENTRY_ACL_OTHER:
		wcscpy(*wp, L"other");
		wname = NULL;
		id = -1;
		break;
	case ARCHIVE_ENTRY_ACL_EVERYONE:
		wcscpy(*wp, L"everyone@");
		wname = NULL;
		id = -1;
		break;
	}
	*wp += wcslen(*wp);
	*(*wp)++ = L':';
	if (((type & ARCHIVE_ENTRY_ACL_TYPE_POSIX1E) != 0) ||
	    tag == ARCHIVE_ENTRY_ACL_USER ||
	    tag == ARCHIVE_ENTRY_ACL_GROUP) {
		if (wname != NULL) {
			wcscpy(*wp, wname);
			*wp += wcslen(*wp);
		} else if (tag == ARCHIVE_ENTRY_ACL_USER
		    || tag == ARCHIVE_ENTRY_ACL_GROUP) {
			append_id_w(wp, id);
			if ((type & ARCHIVE_ENTRY_ACL_TYPE_NFS4) == 0)
				id = -1;
		}
		/* Solaris style has no second colon after other and mask */
		if (((flags & ARCHIVE_ENTRY_ACL_STYLE_SOLARIS) == 0)
		    || (tag != ARCHIVE_ENTRY_ACL_OTHER
		    && tag != ARCHIVE_ENTRY_ACL_MASK))
			*(*wp)++ = L':';
	}
	if ((type & ARCHIVE_ENTRY_ACL_TYPE_POSIX1E) != 0) {
		/* POSIX.1e ACL perms */
		*(*wp)++ = (perm & 0444) ? L'r' : L'-';
		*(*wp)++ = (perm & 0222) ? L'w' : L'-';
		*(*wp)++ = (perm & 0111) ? L'x' : L'-';
	} else {
		/* NFSv4 ACL perms */
		for (i = 0; i < nfsv4_acl_perm_map_size; i++) {
			if (perm & nfsv4_acl_perm_map[i].perm)
				*(*wp)++ = nfsv4_acl_perm_map[i].wc;
			else if ((flags & ARCHIVE_ENTRY_ACL_STYLE_COMPACT) == 0)
				*(*wp)++ = L'-';
		}
		*(*wp)++ = L':';
		for (i = 0; i < nfsv4_acl_flag_map_size; i++) {
			if (perm & nfsv4_acl_flag_map[i].perm)
				*(*wp)++ = nfsv4_acl_flag_map[i].wc;
			else if ((flags & ARCHIVE_ENTRY_ACL_STYLE_COMPACT) == 0)
				*(*wp)++ = L'-';
		}
		*(*wp)++ = L':';
		switch (type) {
		case ARCHIVE_ENTRY_ACL_TYPE_ALLOW:
			wcscpy(*wp, L"allow");
			break;
		case ARCHIVE_ENTRY_ACL_TYPE_DENY:
			wcscpy(*wp, L"deny");
			break;
		case ARCHIVE_ENTRY_ACL_TYPE_AUDIT:
			wcscpy(*wp, L"audit");
			break;
		case ARCHIVE_ENTRY_ACL_TYPE_ALARM:
			wcscpy(*wp, L"alarm");
			break;
		default:
			break;
		}
		*wp += wcslen(*wp);
	}
	if (id != -1) {
		*(*wp)++ = L':';
		append_id_w(wp, id);
	}
}