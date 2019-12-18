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
 int POSIX1E_ACL_ACCESS_EXTATTR_NAMESPACE ; 
 int POSIX1E_ACL_DEFAULT_EXTATTR_NAMESPACE ; 

__attribute__((used)) static const char *
ext2_extattr_name_to_linux(int attrnamespace, const char *name)
{

	if (attrnamespace == POSIX1E_ACL_DEFAULT_EXTATTR_NAMESPACE ||
	    attrnamespace == POSIX1E_ACL_ACCESS_EXTATTR_NAMESPACE)
		return ("");
	else
		return (name);
}