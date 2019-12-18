#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ref {int status; int forced_update; int /*<<< orphan*/  old_oid; int /*<<< orphan*/  new_oid; int /*<<< orphan*/  name; scalar_t__ deletion; int /*<<< orphan*/  old_oid_expect; scalar_t__ expect_old_sha1; TYPE_1__* peer_ref; scalar_t__ force; struct ref* next; } ;
struct TYPE_2__ {int /*<<< orphan*/  new_oid; } ;

/* Variables and functions */
 int REF_STATUS_REJECT_ALREADY_EXISTS ; 
 int REF_STATUS_REJECT_FETCH_FIRST ; 
 int REF_STATUS_REJECT_NEEDS_FORCE ; 
 int REF_STATUS_REJECT_NONFASTFORWARD ; 
 int REF_STATUS_REJECT_STALE ; 
 int REF_STATUS_UPTODATE ; 
 int /*<<< orphan*/  has_object_file (int /*<<< orphan*/ *) ; 
 scalar_t__ is_null_oid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lookup_commit_reference_gently (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ oideq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ref_newer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ starts_with (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  the_repository ; 

void set_ref_status_for_push(struct ref *remote_refs, int send_mirror,
			     int force_update)
{
	struct ref *ref;

	for (ref = remote_refs; ref; ref = ref->next) {
		int force_ref_update = ref->force || force_update;
		int reject_reason = 0;

		if (ref->peer_ref)
			oidcpy(&ref->new_oid, &ref->peer_ref->new_oid);
		else if (!send_mirror)
			continue;

		ref->deletion = is_null_oid(&ref->new_oid);
		if (!ref->deletion &&
			oideq(&ref->old_oid, &ref->new_oid)) {
			ref->status = REF_STATUS_UPTODATE;
			continue;
		}

		/*
		 * If the remote ref has moved and is now different
		 * from what we expect, reject any push.
		 *
		 * It also is an error if the user told us to check
		 * with the remote-tracking branch to find the value
		 * to expect, but we did not have such a tracking
		 * branch.
		 */
		if (ref->expect_old_sha1) {
			if (!oideq(&ref->old_oid, &ref->old_oid_expect))
				reject_reason = REF_STATUS_REJECT_STALE;
			else
				/* If the ref isn't stale then force the update. */
				force_ref_update = 1;
		}

		/*
		 * If the update isn't already rejected then check
		 * the usual "must fast-forward" rules.
		 *
		 * Decide whether an individual refspec A:B can be
		 * pushed.  The push will succeed if any of the
		 * following are true:
		 *
		 * (1) the remote reference B does not exist
		 *
		 * (2) the remote reference B is being removed (i.e.,
		 *     pushing :B where no source is specified)
		 *
		 * (3) the destination is not under refs/tags/, and
		 *     if the old and new value is a commit, the new
		 *     is a descendant of the old.
		 *
		 * (4) it is forced using the +A:B notation, or by
		 *     passing the --force argument
		 */

		if (!reject_reason && !ref->deletion && !is_null_oid(&ref->old_oid)) {
			if (starts_with(ref->name, "refs/tags/"))
				reject_reason = REF_STATUS_REJECT_ALREADY_EXISTS;
			else if (!has_object_file(&ref->old_oid))
				reject_reason = REF_STATUS_REJECT_FETCH_FIRST;
			else if (!lookup_commit_reference_gently(the_repository, &ref->old_oid, 1) ||
				 !lookup_commit_reference_gently(the_repository, &ref->new_oid, 1))
				reject_reason = REF_STATUS_REJECT_NEEDS_FORCE;
			else if (!ref_newer(&ref->new_oid, &ref->old_oid))
				reject_reason = REF_STATUS_REJECT_NONFASTFORWARD;
		}

		/*
		 * "--force" will defeat any rejection implemented
		 * by the rules above.
		 */
		if (!force_ref_update)
			ref->status = reject_reason;
		else if (reject_reason)
			ref->forced_update = 1;
	}
}