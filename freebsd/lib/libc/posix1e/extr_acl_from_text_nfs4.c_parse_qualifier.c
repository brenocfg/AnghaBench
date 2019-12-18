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
typedef  int /*<<< orphan*/  acl_tag_t ;
typedef  int /*<<< orphan*/  acl_entry_t ;

/* Variables and functions */
 int _acl_name_to_id (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int acl_get_tag_type (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int acl_set_qualifier (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static int
parse_qualifier(char *str, acl_entry_t entry, int *need_qualifier)
{
	int qualifier_length, error;
	uid_t id;
	acl_tag_t tag;

	assert(need_qualifier != NULL);
	*need_qualifier = 0;

	qualifier_length = strlen(str);

	if (qualifier_length == 0) {
		warnx("malformed ACL: empty \"qualifier\" field");
		return (-1);
	}

	error = acl_get_tag_type(entry, &tag);
	if (error)
		return (error);

	error = _acl_name_to_id(tag, str, &id);
	if (error) {
		*need_qualifier = 1;
		return (0);
	}

	return (acl_set_qualifier(entry, &id));
}