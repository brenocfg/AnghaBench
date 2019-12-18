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
 int /*<<< orphan*/  EINVAL ; 
#define  EXTATTR_NAMESPACE_SYSTEM 129 
 int /*<<< orphan*/  EXTATTR_NAMESPACE_SYSTEM_STRING ; 
#define  EXTATTR_NAMESPACE_USER 128 
 int /*<<< orphan*/  EXTATTR_NAMESPACE_USER_STRING ; 
 int /*<<< orphan*/  errno ; 
 char* strdup (int /*<<< orphan*/ ) ; 

int
extattr_namespace_to_string(int attrnamespace, char **string)
{

	switch(attrnamespace) {
	case EXTATTR_NAMESPACE_USER:
		if (string != NULL)
			*string = strdup(EXTATTR_NAMESPACE_USER_STRING);
		return (0);

	case EXTATTR_NAMESPACE_SYSTEM:
		if (string != NULL)
			*string = strdup(EXTATTR_NAMESPACE_SYSTEM_STRING);
		return (0);

	default:
		errno = EINVAL;
		return (-1);
	}
}