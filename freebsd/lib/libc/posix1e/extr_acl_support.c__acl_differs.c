#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct acl_entry {scalar_t__ ae_tag; scalar_t__ ae_id; scalar_t__ ae_perm; scalar_t__ ae_entry_type; scalar_t__ ae_flags; } ;
typedef  TYPE_2__* acl_t ;
struct TYPE_6__ {int acl_cnt; struct acl_entry* acl_entry; } ;
struct TYPE_7__ {TYPE_1__ ats_acl; } ;

/* Variables and functions */
 scalar_t__ ACL_BRAND_UNKNOWN ; 
 scalar_t__ _acl_brand (TYPE_2__* const) ; 
 int /*<<< orphan*/  assert (int) ; 

int
_acl_differs(const acl_t a, const acl_t b)
{
	int i;
	struct acl_entry *entrya, *entryb;

	assert(_acl_brand(a) == _acl_brand(b));
	assert(_acl_brand(a) != ACL_BRAND_UNKNOWN);
	assert(_acl_brand(b) != ACL_BRAND_UNKNOWN);

	if (a->ats_acl.acl_cnt != b->ats_acl.acl_cnt)
		return (1);

	for (i = 0; i < b->ats_acl.acl_cnt; i++) {
		entrya = &(a->ats_acl.acl_entry[i]);
		entryb = &(b->ats_acl.acl_entry[i]);

		if (entrya->ae_tag != entryb->ae_tag ||
		    entrya->ae_id != entryb->ae_id ||
		    entrya->ae_perm != entryb->ae_perm ||
		    entrya->ae_entry_type != entryb->ae_entry_type ||
		    entrya->ae_flags != entryb->ae_flags)
			return (1);
	}

	return (0);
}