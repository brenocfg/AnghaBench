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
 int EXTATTR_NAMESPACE_SYSTEM ; 
 int /*<<< orphan*/  EXTATTR_NAMESPACE_SYSTEM_STRING ; 
 int EXTATTR_NAMESPACE_USER ; 
 int /*<<< orphan*/  EXTATTR_NAMESPACE_USER_STRING ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

int
extattr_string_to_namespace(const char *string, int *attrnamespace)
{

	if (!strcmp(string, EXTATTR_NAMESPACE_USER_STRING)) {
		if (attrnamespace != NULL)
			*attrnamespace = EXTATTR_NAMESPACE_USER;
		return (0);
	} else if (!strcmp(string, EXTATTR_NAMESPACE_SYSTEM_STRING)) {
		if (attrnamespace != NULL)
			*attrnamespace = EXTATTR_NAMESPACE_SYSTEM;
		return (0);
	} else {
		errno = EINVAL;
		return (-1);
	}
}