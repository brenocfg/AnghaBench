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
struct passwd {char* pw_name; } ;
struct group {char* gr_name; } ;
typedef  int acl_tag_t ;
typedef  int /*<<< orphan*/  acl_entry_t ;

/* Variables and functions */
#define  ACL_EVERYONE 132 
#define  ACL_GROUP 131 
#define  ACL_GROUP_OBJ 130 
#define  ACL_USER 129 
#define  ACL_USER_OBJ 128 
 scalar_t__ acl_get_qualifier (int /*<<< orphan*/  const) ; 
 int acl_get_tag_type (int /*<<< orphan*/  const,int*) ; 
 struct group* getgrgid (scalar_t__) ; 
 struct passwd* getpwuid (scalar_t__) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,...) ; 

__attribute__((used)) static int
format_who(char *str, size_t size, const acl_entry_t entry, int numeric)
{
	int error;
	acl_tag_t tag;
	struct passwd *pwd;
	struct group *grp;
	uid_t *id;

	error = acl_get_tag_type(entry, &tag);
	if (error)
		return (error);

	switch (tag) {
	case ACL_USER_OBJ:
		snprintf(str, size, "owner@");
		break;

	case ACL_USER:
		id = (uid_t *)acl_get_qualifier(entry);
		if (id == NULL)
			return (-1);
		/* XXX: Thread-unsafe. */
		if (!numeric)
			pwd = getpwuid(*id);
		else
			pwd = NULL;
		if (pwd == NULL)
			snprintf(str, size, "user:%d", (unsigned int)*id);
		else
			snprintf(str, size, "user:%s", pwd->pw_name);
		break;

	case ACL_GROUP_OBJ:
		snprintf(str, size, "group@");
		break;

	case ACL_GROUP:
		id = (uid_t *)acl_get_qualifier(entry);
		if (id == NULL)
			return (-1);
		/* XXX: Thread-unsafe. */
		if (!numeric)
			grp = getgrgid(*id);
		else
			grp = NULL;
		if (grp == NULL)
			snprintf(str, size, "group:%d", (unsigned int)*id);
		else
			snprintf(str, size, "group:%s", grp->gr_name);
		break;

	case ACL_EVERYONE:
		snprintf(str, size, "everyone@");
		break;

	default:
		return (-1);
	}

	return (0);
}