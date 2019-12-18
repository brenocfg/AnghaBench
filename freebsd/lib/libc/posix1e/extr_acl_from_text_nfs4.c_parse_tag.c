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
 int /*<<< orphan*/  ACL_EVERYONE ; 
 int /*<<< orphan*/  ACL_GROUP ; 
 int /*<<< orphan*/  ACL_GROUP_OBJ ; 
 int /*<<< orphan*/  ACL_USER ; 
 int /*<<< orphan*/  ACL_USER_OBJ ; 
 int acl_set_tag_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static int
parse_tag(const char *str, acl_entry_t entry, int *need_qualifier)
{

	assert(need_qualifier != NULL);
	*need_qualifier = 0;

	if (strcmp(str, "owner@") == 0)
		return (acl_set_tag_type(entry, ACL_USER_OBJ));
	if (strcmp(str, "group@") == 0)
		return (acl_set_tag_type(entry, ACL_GROUP_OBJ));
	if (strcmp(str, "everyone@") == 0)
		return (acl_set_tag_type(entry, ACL_EVERYONE));

	*need_qualifier = 1;

	if (strcmp(str, "user") == 0 || strcmp(str, "u") == 0)
		return (acl_set_tag_type(entry, ACL_USER));
	if (strcmp(str, "group") == 0 || strcmp(str, "g") == 0)
		return (acl_set_tag_type(entry, ACL_GROUP));

	warnx("malformed ACL: invalid \"tag\" field");

	return (-1);
}