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
typedef  int /*<<< orphan*/  acl_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_ENTRY_TYPE_ALARM ; 
 int /*<<< orphan*/  ACL_ENTRY_TYPE_ALLOW ; 
 int /*<<< orphan*/  ACL_ENTRY_TYPE_AUDIT ; 
 int /*<<< orphan*/  ACL_ENTRY_TYPE_DENY ; 
 int acl_set_entry_type_np (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static int
parse_entry_type(const char *str, acl_entry_t entry)
{

	if (strcmp(str, "allow") == 0)
		return (acl_set_entry_type_np(entry, ACL_ENTRY_TYPE_ALLOW));
	if (strcmp(str, "deny") == 0)
		return (acl_set_entry_type_np(entry, ACL_ENTRY_TYPE_DENY));
	if (strcmp(str, "audit") == 0)
		return (acl_set_entry_type_np(entry, ACL_ENTRY_TYPE_AUDIT));
	if (strcmp(str, "alarm") == 0)
		return (acl_set_entry_type_np(entry, ACL_ENTRY_TYPE_ALARM));

	warnx("malformed ACL: invalid \"type\" field");

	return (-1);
}