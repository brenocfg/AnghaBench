#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* acl_entry_t ;
struct TYPE_5__ {int /*<<< orphan*/  ae_id; int /*<<< orphan*/  ae_tag; int /*<<< orphan*/  ae_entry_type; } ;

/* Variables and functions */
#define  ACL_BRAND_NFS4 128 
 int /*<<< orphan*/  ACL_GROUP ; 
 int /*<<< orphan*/  ACL_USER ; 
 int _entry_brand (TYPE_1__* const) ; 

__attribute__((used)) static int
_entry_matches(const acl_entry_t a, const acl_entry_t b)
{
	/*
	 * There is a semantical difference here between NFSv4 and POSIX
	 * draft ACLs.  In POSIX, there may be only one entry for the particular
	 * user or group.  In NFSv4 ACL, there may be any number of them.  We're
	 * trying to be more specific here in that case.
	 */
	switch (_entry_brand(a)) {
	case ACL_BRAND_NFS4:
		if (a->ae_tag != b->ae_tag || a->ae_entry_type != b->ae_entry_type)
			return (0);

		/* If ae_ids matter, compare them as well. */
		if (a->ae_tag == ACL_USER || a->ae_tag == ACL_GROUP) {
			if (a->ae_id != b->ae_id)
				return (0);
		}

		return (1);

	default:
		if ((a->ae_tag == b->ae_tag) && (a->ae_id == b->ae_id))
			return (1);
	}

	return (0);
}