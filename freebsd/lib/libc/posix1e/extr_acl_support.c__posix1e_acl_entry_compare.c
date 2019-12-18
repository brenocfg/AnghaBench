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
struct acl_entry {scalar_t__ ae_tag; scalar_t__ ae_id; } ;

/* Variables and functions */
 scalar_t__ ACL_BRAND_POSIX ; 
 scalar_t__ ACL_GROUP ; 
 scalar_t__ ACL_USER ; 
 scalar_t__ _entry_brand (struct acl_entry*) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int
_posix1e_acl_entry_compare(struct acl_entry *a, struct acl_entry *b)
{

	assert(_entry_brand(a) == ACL_BRAND_POSIX);
	assert(_entry_brand(b) == ACL_BRAND_POSIX);

	/*
	 * First, sort between tags -- conveniently defined in the correct
	 * order for verification.
	 */
	if (a->ae_tag < b->ae_tag)
		return (-1);
	if (a->ae_tag > b->ae_tag)
		return (1);

	/*
	 * Next compare uids/gids on appropriate types.
	 */

	if (a->ae_tag == ACL_USER || a->ae_tag == ACL_GROUP) {
		if (a->ae_id < b->ae_id)
			return (-1);
		if (a->ae_id > b->ae_id)
			return (1);

		/* shouldn't be equal, fall through to the invalid case */
	}

	/*
	 * Don't know how to sort multiple entries of the rest--either it's
	 * a bad entry, or there shouldn't be more than one.  Ignore and the
	 * validity checker can get it later.
	 */
	return (0);
}