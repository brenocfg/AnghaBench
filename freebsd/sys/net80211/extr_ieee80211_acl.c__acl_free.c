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
struct aclstate {int /*<<< orphan*/  as_nacls; int /*<<< orphan*/  as_list; } ;
struct acl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_LOCK_ASSERT (struct aclstate*) ; 
 int /*<<< orphan*/  IEEE80211_FREE (struct acl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct acl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_80211_ACL ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct acl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acl_hash ; 
 int /*<<< orphan*/  acl_list ; 

__attribute__((used)) static void
_acl_free(struct aclstate *as, struct acl *acl)
{
	ACL_LOCK_ASSERT(as);

	TAILQ_REMOVE(&as->as_list, acl, acl_list);
	LIST_REMOVE(acl, acl_hash);
	IEEE80211_FREE(acl, M_80211_ACL);
	as->as_nacls--;
}