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
typedef  void* uid_t ;
struct acl_entry {int ae_tag; void* ae_id; scalar_t__ ae_flags; scalar_t__ ae_entry_type; int /*<<< orphan*/  ae_perm; } ;
typedef  int /*<<< orphan*/  mode_t ;
typedef  void* gid_t ;
typedef  int acl_tag_t ;

/* Variables and functions */
#define  ACL_GROUP_OBJ 130 
#define  ACL_OTHER 129 
 void* ACL_UNDEFINED_ID ; 
#define  ACL_USER_OBJ 128 
 int /*<<< orphan*/  acl_posix1e_mode_to_perm (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

struct acl_entry
acl_posix1e_mode_to_entry(acl_tag_t tag, uid_t uid, gid_t gid, mode_t mode)
{
	struct acl_entry	acl_entry;

	acl_entry.ae_tag = tag;
	acl_entry.ae_perm = acl_posix1e_mode_to_perm(tag, mode);
	acl_entry.ae_entry_type = 0;
	acl_entry.ae_flags = 0;
	switch(tag) {
	case ACL_USER_OBJ:
		acl_entry.ae_id = uid;
		break;

	case ACL_GROUP_OBJ:
		acl_entry.ae_id = gid;
		break;

	case ACL_OTHER:
		acl_entry.ae_id = ACL_UNDEFINED_ID;
		break;

	default:
		acl_entry.ae_id = ACL_UNDEFINED_ID;
		printf("acl_posix1e_mode_to_entry: invalid tag (%d)\n", tag);
	}

	return (acl_entry);
}