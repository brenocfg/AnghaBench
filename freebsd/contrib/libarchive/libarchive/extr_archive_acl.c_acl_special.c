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
struct archive_acl {int mode; } ;

/* Variables and functions */
#define  ARCHIVE_ENTRY_ACL_GROUP_OBJ 130 
#define  ARCHIVE_ENTRY_ACL_OTHER 129 
 int ARCHIVE_ENTRY_ACL_TYPE_ACCESS ; 
#define  ARCHIVE_ENTRY_ACL_USER_OBJ 128 

__attribute__((used)) static int
acl_special(struct archive_acl *acl, int type, int permset, int tag)
{
	if (type == ARCHIVE_ENTRY_ACL_TYPE_ACCESS
	    && ((permset & ~007) == 0)) {
		switch (tag) {
		case ARCHIVE_ENTRY_ACL_USER_OBJ:
			acl->mode &= ~0700;
			acl->mode |= (permset & 7) << 6;
			return (0);
		case ARCHIVE_ENTRY_ACL_GROUP_OBJ:
			acl->mode &= ~0070;
			acl->mode |= (permset & 7) << 3;
			return (0);
		case ARCHIVE_ENTRY_ACL_OTHER:
			acl->mode &= ~0007;
			acl->mode |= permset & 7;
			return (0);
		}
	}
	return (1);
}