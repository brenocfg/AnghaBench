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
struct acl_entry {scalar_t__ ae_flags; int /*<<< orphan*/  ae_entry_type; int /*<<< orphan*/  ae_perm; int /*<<< orphan*/  ae_id; int /*<<< orphan*/  ae_tag; } ;
struct acl {int acl_cnt; struct acl_entry* acl_entry; } ;
typedef  int /*<<< orphan*/  acl_tag_t ;
typedef  int /*<<< orphan*/  acl_perm_t ;
typedef  int /*<<< orphan*/  acl_entry_type_t ;

/* Variables and functions */
 int ACL_MAX_ENTRIES ; 
 int /*<<< orphan*/  ACL_UNDEFINED_ID ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 

__attribute__((used)) static struct acl_entry *
_acl_append(struct acl *aclp, acl_tag_t tag, acl_perm_t perm,
    acl_entry_type_t entry_type)
{
	struct acl_entry *entry;

	KASSERT(aclp->acl_cnt + 1 <= ACL_MAX_ENTRIES,
	    ("aclp->acl_cnt + 1 <= ACL_MAX_ENTRIES"));

	entry = &(aclp->acl_entry[aclp->acl_cnt]);
	aclp->acl_cnt++;

	entry->ae_tag = tag;
	entry->ae_id = ACL_UNDEFINED_ID;
	entry->ae_perm = perm;
	entry->ae_entry_type = entry_type;
	entry->ae_flags = 0;

	return (entry);
}