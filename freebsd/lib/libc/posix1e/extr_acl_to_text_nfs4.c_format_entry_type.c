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
typedef  int acl_entry_type_t ;
typedef  int /*<<< orphan*/  acl_entry_t ;

/* Variables and functions */
#define  ACL_ENTRY_TYPE_ALARM 131 
#define  ACL_ENTRY_TYPE_ALLOW 130 
#define  ACL_ENTRY_TYPE_AUDIT 129 
#define  ACL_ENTRY_TYPE_DENY 128 
 int acl_get_entry_type_np (int /*<<< orphan*/  const,int*) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*) ; 

__attribute__((used)) static int
format_entry_type(char *str, size_t size, const acl_entry_t entry)
{
	int error;
	acl_entry_type_t entry_type;

	error = acl_get_entry_type_np(entry, &entry_type);
	if (error)
		return (error);

	switch (entry_type) {
	case ACL_ENTRY_TYPE_ALLOW:
		snprintf(str, size, "allow");
		break;
	case ACL_ENTRY_TYPE_DENY:
		snprintf(str, size, "deny");
		break;
	case ACL_ENTRY_TYPE_AUDIT:
		snprintf(str, size, "audit");
		break;
	case ACL_ENTRY_TYPE_ALARM:
		snprintf(str, size, "alarm");
		break;
	default:
		return (-1);
	}

	return (0);
}