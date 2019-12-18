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
typedef  int /*<<< orphan*/  uid_t ;
typedef  int acl_tag_t ;
typedef  int /*<<< orphan*/  acl_t ;
typedef  int /*<<< orphan*/  acl_perm_t ;

/* Variables and functions */
 scalar_t__ ACL_BRAND_POSIX ; 
#define  ACL_GROUP 133 
#define  ACL_GROUP_OBJ 132 
#define  ACL_MASK 131 
#define  ACL_OTHER 130 
#define  ACL_USER 129 
#define  ACL_USER_OBJ 128 
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ _acl_brand (int /*<<< orphan*/ ) ; 
 int _acl_name_to_id (int,char*,int /*<<< orphan*/ *) ; 
 int _posix1e_acl_add_entry (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int _posix1e_acl_string_to_perm (char*,int /*<<< orphan*/ *) ; 
 int acl_string_to_tag (char*,char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  errno ; 
 char* string_skip_whitespace (char*) ; 
 int /*<<< orphan*/  string_trim_trailing_whitespace (char*) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static int
_posix1e_acl_entry_from_text(acl_t aclp, char *entry)
{
	acl_tag_t	 t;
	acl_perm_t	 p;
	char		*tag, *qualifier, *permission;
	uid_t		 id;
	int		 error;

	assert(_acl_brand(aclp) == ACL_BRAND_POSIX);

	/* Split into three ':' delimited fields. */
	tag = strsep(&entry, ":");
	if (tag == NULL) {
		errno = EINVAL;
		return (-1);
	}
	tag = string_skip_whitespace(tag);
	if ((*tag == '\0') && (!entry)) {
		/*
		 * Is an entirely comment line, skip to next
		 * comma.
		 */
		return (0);
	}
	string_trim_trailing_whitespace(tag);

	qualifier = strsep(&entry, ":");
	if (qualifier == NULL) {
		errno = EINVAL;
		return (-1);
	}
	qualifier = string_skip_whitespace(qualifier);
	string_trim_trailing_whitespace(qualifier);

	permission = strsep(&entry, ":");
	if (permission == NULL || entry) {
		errno = EINVAL;
		return (-1);
	}
	permission = string_skip_whitespace(permission);
	string_trim_trailing_whitespace(permission);

	t = acl_string_to_tag(tag, qualifier);
	if (t == -1) {
		errno = EINVAL;
		return (-1);
	}

	error = _posix1e_acl_string_to_perm(permission, &p);
	if (error == -1) {
		errno = EINVAL;
		return (-1);
	}		

	switch(t) {
		case ACL_USER_OBJ:
		case ACL_GROUP_OBJ:
		case ACL_MASK:
		case ACL_OTHER:
			if (*qualifier != '\0') {
				errno = EINVAL;
				return (-1);
			}
			id = 0;
			break;

		case ACL_USER:
		case ACL_GROUP:
			error = _acl_name_to_id(t, qualifier, &id);
			if (error == -1)
				return (-1);
			break;

		default:
			errno = EINVAL;
			return (-1);
	}

	error = _posix1e_acl_add_entry(aclp, t, id, p);
	if (error == -1)
		return (-1);

	return (0);
}