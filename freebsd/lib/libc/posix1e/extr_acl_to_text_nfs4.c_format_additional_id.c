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
typedef  scalar_t__ uid_t ;
typedef  int acl_tag_t ;
typedef  int /*<<< orphan*/  acl_entry_t ;

/* Variables and functions */
#define  ACL_EVERYONE 130 
#define  ACL_GROUP_OBJ 129 
#define  ACL_USER_OBJ 128 
 scalar_t__ acl_get_qualifier (int /*<<< orphan*/  const) ; 
 int acl_get_tag_type (int /*<<< orphan*/  const,int*) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,unsigned int) ; 

__attribute__((used)) static int
format_additional_id(char *str, size_t size, const acl_entry_t entry)
{
	int error;
	acl_tag_t tag;
	uid_t *id;

	error = acl_get_tag_type(entry, &tag);
	if (error)
		return (error);

	switch (tag) {
	case ACL_USER_OBJ:
	case ACL_GROUP_OBJ:
	case ACL_EVERYONE:
		str[0] = '\0';
		break;

	default:
		id = (uid_t *)acl_get_qualifier(entry);
		if (id == NULL)
			return (-1);
		snprintf(str, size, ":%d", (unsigned int)*id);
	}

	return (0);
}