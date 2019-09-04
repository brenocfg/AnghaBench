#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct transport {TYPE_2__* remote; } ;
struct ref {scalar_t__ status; char* name; TYPE_1__* peer_ref; int /*<<< orphan*/  new_oid; struct ref* next; } ;
struct TYPE_4__ {char* name; } ;
struct TYPE_3__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRANCH_CONFIG_VERBOSE ; 
 int REF_ISSYMREF ; 
 scalar_t__ REF_STATUS_OK ; 
 scalar_t__ REF_STATUS_UPTODATE ; 
 int /*<<< orphan*/  RESOLVE_REF_READING ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  install_branch_config (int /*<<< orphan*/ ,char const*,char*,char const*) ; 
 scalar_t__ is_null_oid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char const*,char const*,char*) ; 
 char* resolve_ref_unsafe (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ starts_with (char const*,char*) ; 

__attribute__((used)) static void set_upstreams(struct transport *transport, struct ref *refs,
	int pretend)
{
	struct ref *ref;
	for (ref = refs; ref; ref = ref->next) {
		const char *localname;
		const char *tmp;
		const char *remotename;
		int flag = 0;
		/*
		 * Check suitability for tracking. Must be successful /
		 * already up-to-date ref create/modify (not delete).
		 */
		if (ref->status != REF_STATUS_OK &&
			ref->status != REF_STATUS_UPTODATE)
			continue;
		if (!ref->peer_ref)
			continue;
		if (is_null_oid(&ref->new_oid))
			continue;

		/* Follow symbolic refs (mainly for HEAD). */
		localname = ref->peer_ref->name;
		remotename = ref->name;
		tmp = resolve_ref_unsafe(localname, RESOLVE_REF_READING,
					 NULL, &flag);
		if (tmp && flag & REF_ISSYMREF &&
			starts_with(tmp, "refs/heads/"))
			localname = tmp;

		/* Both source and destination must be local branches. */
		if (!localname || !starts_with(localname, "refs/heads/"))
			continue;
		if (!remotename || !starts_with(remotename, "refs/heads/"))
			continue;

		if (!pretend)
			install_branch_config(BRANCH_CONFIG_VERBOSE,
				localname + 11, transport->remote->name,
				remotename);
		else
			printf(_("Would set upstream of '%s' to '%s' of '%s'\n"),
				localname + 11, remotename + 11,
				transport->remote->name);
	}
}