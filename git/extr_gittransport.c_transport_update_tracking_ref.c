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
struct refspec_item {char* dst; int /*<<< orphan*/  src; } ;
struct ref {scalar_t__ status; int /*<<< orphan*/  new_oid; scalar_t__ deletion; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ REF_STATUS_OK ; 
 scalar_t__ REF_STATUS_UPTODATE ; 
 int /*<<< orphan*/  delete_ref (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  remote_find_tracking (struct remote*,struct refspec_item*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  update_ref (char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void transport_update_tracking_ref(struct remote *remote, struct ref *ref, int verbose)
{
	struct refspec_item rs;

	if (ref->status != REF_STATUS_OK && ref->status != REF_STATUS_UPTODATE)
		return;

	rs.src = ref->name;
	rs.dst = NULL;

	if (!remote_find_tracking(remote, &rs)) {
		if (verbose)
			fprintf(stderr, "updating local tracking ref '%s'\n", rs.dst);
		if (ref->deletion) {
			delete_ref(NULL, rs.dst, NULL, 0);
		} else
			update_ref("update by push", rs.dst, &ref->new_oid,
				   NULL, 0, 0);
		free(rs.dst);
	}
}