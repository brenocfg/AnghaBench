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

/* Variables and functions */
 int EXT4_XATTR_INDEX_POSIX_ACL_ACCESS ; 
 int EXT4_XATTR_INDEX_POSIX_ACL_DEFAULT ; 
 int EXT4_XATTR_INDEX_SYSTEM ; 
 int EXT4_XATTR_INDEX_USER ; 
#define  EXTATTR_NAMESPACE_SYSTEM 129 
#define  EXTATTR_NAMESPACE_USER 128 
 int /*<<< orphan*/  POSIX1E_ACL_ACCESS_EXTATTR_NAME ; 
 int POSIX1E_ACL_ACCESS_EXTATTR_NAMESPACE ; 
 int /*<<< orphan*/  POSIX1E_ACL_DEFAULT_EXTATTR_NAME ; 
 int POSIX1E_ACL_DEFAULT_EXTATTR_NAMESPACE ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ext2_extattr_attrnamespace_to_linux(int attrnamespace, const char *name)
{

	if (attrnamespace == POSIX1E_ACL_DEFAULT_EXTATTR_NAMESPACE &&
	    !strcmp(name, POSIX1E_ACL_DEFAULT_EXTATTR_NAME))
		return (EXT4_XATTR_INDEX_POSIX_ACL_DEFAULT);

	if (attrnamespace == POSIX1E_ACL_ACCESS_EXTATTR_NAMESPACE &&
	    !strcmp(name, POSIX1E_ACL_ACCESS_EXTATTR_NAME))
		return (EXT4_XATTR_INDEX_POSIX_ACL_ACCESS);

	switch (attrnamespace) {
	case EXTATTR_NAMESPACE_SYSTEM:
		return (EXT4_XATTR_INDEX_SYSTEM);

	case EXTATTR_NAMESPACE_USER:
		return (EXT4_XATTR_INDEX_USER);
	}

	/*
	 * In this case namespace conversion should be unique,
	 * so this point is unreachable.
	 */
	return (-1);
}