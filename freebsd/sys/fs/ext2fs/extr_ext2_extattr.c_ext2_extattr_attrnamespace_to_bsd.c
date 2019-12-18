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
#define  EXT4_XATTR_INDEX_POSIX_ACL_ACCESS 131 
#define  EXT4_XATTR_INDEX_POSIX_ACL_DEFAULT 130 
#define  EXT4_XATTR_INDEX_SYSTEM 129 
#define  EXT4_XATTR_INDEX_USER 128 
 int EXTATTR_NAMESPACE_EMPTY ; 
 int EXTATTR_NAMESPACE_SYSTEM ; 
 int EXTATTR_NAMESPACE_USER ; 
 int POSIX1E_ACL_ACCESS_EXTATTR_NAMESPACE ; 
 int POSIX1E_ACL_DEFAULT_EXTATTR_NAMESPACE ; 

__attribute__((used)) static int
ext2_extattr_attrnamespace_to_bsd(int attrnamespace)
{

	switch (attrnamespace) {
	case EXT4_XATTR_INDEX_SYSTEM:
		return (EXTATTR_NAMESPACE_SYSTEM);

	case EXT4_XATTR_INDEX_USER:
		return (EXTATTR_NAMESPACE_USER);

	case EXT4_XATTR_INDEX_POSIX_ACL_DEFAULT:
		return (POSIX1E_ACL_DEFAULT_EXTATTR_NAMESPACE);

	case EXT4_XATTR_INDEX_POSIX_ACL_ACCESS:
		return (POSIX1E_ACL_ACCESS_EXTATTR_NAMESPACE);
	}

	return (EXTATTR_NAMESPACE_EMPTY);
}