#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct archive_acl {int acl_state; int mode; TYPE_1__* acl_p; TYPE_1__* acl_head; } ;
struct archive {int dummy; } ;
struct TYPE_2__ {int type; int permset; int tag; int id; struct TYPE_2__* next; int /*<<< orphan*/  name; } ;

/* Variables and functions */
#define  ARCHIVE_ENTRY_ACL_GROUP_OBJ 130 
#define  ARCHIVE_ENTRY_ACL_OTHER 129 
 int ARCHIVE_ENTRY_ACL_TYPE_ACCESS ; 
#define  ARCHIVE_ENTRY_ACL_USER_OBJ 128 
 int ARCHIVE_EOF ; 
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int ARCHIVE_WARN ; 
 scalar_t__ ENOMEM ; 
 scalar_t__ archive_mstring_get_mbs (struct archive*,int /*<<< orphan*/ *,char const**) ; 
 scalar_t__ errno ; 

int
archive_acl_next(struct archive *a, struct archive_acl *acl, int want_type,
    int *type, int *permset, int *tag, int *id, const char **name)
{
	*name = NULL;
	*id = -1;

	/*
	 * The acl_state is either zero (no entries available), -1
	 * (reading from list), or an entry type (retrieve that type
	 * from ae_stat.aest_mode).
	 */
	if (acl->acl_state == 0)
		return (ARCHIVE_WARN);

	/* The first three access entries are special. */
	if ((want_type & ARCHIVE_ENTRY_ACL_TYPE_ACCESS) != 0) {
		switch (acl->acl_state) {
		case ARCHIVE_ENTRY_ACL_USER_OBJ:
			*permset = (acl->mode >> 6) & 7;
			*type = ARCHIVE_ENTRY_ACL_TYPE_ACCESS;
			*tag = ARCHIVE_ENTRY_ACL_USER_OBJ;
			acl->acl_state = ARCHIVE_ENTRY_ACL_GROUP_OBJ;
			return (ARCHIVE_OK);
		case ARCHIVE_ENTRY_ACL_GROUP_OBJ:
			*permset = (acl->mode >> 3) & 7;
			*type = ARCHIVE_ENTRY_ACL_TYPE_ACCESS;
			*tag = ARCHIVE_ENTRY_ACL_GROUP_OBJ;
			acl->acl_state = ARCHIVE_ENTRY_ACL_OTHER;
			return (ARCHIVE_OK);
		case ARCHIVE_ENTRY_ACL_OTHER:
			*permset = acl->mode & 7;
			*type = ARCHIVE_ENTRY_ACL_TYPE_ACCESS;
			*tag = ARCHIVE_ENTRY_ACL_OTHER;
			acl->acl_state = -1;
			acl->acl_p = acl->acl_head;
			return (ARCHIVE_OK);
		default:
			break;
		}
	}

	while (acl->acl_p != NULL && (acl->acl_p->type & want_type) == 0)
		acl->acl_p = acl->acl_p->next;
	if (acl->acl_p == NULL) {
		acl->acl_state = 0;
		*type = 0;
		*permset = 0;
		*tag = 0;
		*id = -1;
		*name = NULL;
		return (ARCHIVE_EOF); /* End of ACL entries. */
	}
	*type = acl->acl_p->type;
	*permset = acl->acl_p->permset;
	*tag = acl->acl_p->tag;
	*id = acl->acl_p->id;
	if (archive_mstring_get_mbs(a, &acl->acl_p->name, name) != 0) {
		if (errno == ENOMEM)
			return (ARCHIVE_FATAL);
		*name = NULL;
	}
	acl->acl_p = acl->acl_p->next;
	return (ARCHIVE_OK);
}