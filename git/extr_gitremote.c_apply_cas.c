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
struct remote {int dummy; } ;
struct ref {int expect_old_sha1; int /*<<< orphan*/  old_oid_expect; int /*<<< orphan*/  name; } ;
struct push_cas_option {int nr; int /*<<< orphan*/  use_tracking_for_rest; struct push_cas* entry; } ;
struct push_cas {int /*<<< orphan*/  expect; int /*<<< orphan*/  use_tracking; int /*<<< orphan*/  refname; } ;

/* Variables and functions */
 int /*<<< orphan*/  oidclr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refname_match (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ remote_tracking (struct remote*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void apply_cas(struct push_cas_option *cas,
		      struct remote *remote,
		      struct ref *ref)
{
	int i;

	/* Find an explicit --<option>=<name>[:<value>] entry */
	for (i = 0; i < cas->nr; i++) {
		struct push_cas *entry = &cas->entry[i];
		if (!refname_match(entry->refname, ref->name))
			continue;
		ref->expect_old_sha1 = 1;
		if (!entry->use_tracking)
			oidcpy(&ref->old_oid_expect, &entry->expect);
		else if (remote_tracking(remote, ref->name, &ref->old_oid_expect))
			oidclr(&ref->old_oid_expect);
		return;
	}

	/* Are we using "--<option>" to cover all? */
	if (!cas->use_tracking_for_rest)
		return;

	ref->expect_old_sha1 = 1;
	if (remote_tracking(remote, ref->name, &ref->old_oid_expect))
		oidclr(&ref->old_oid_expect);
}