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
typedef  int /*<<< orphan*/  timestamp_t ;
struct object_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  fprintf_ln (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsck_handle_reflog_oid (char const*,struct object_id*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ verbose ; 

__attribute__((used)) static int fsck_handle_reflog_ent(struct object_id *ooid, struct object_id *noid,
		const char *email, timestamp_t timestamp, int tz,
		const char *message, void *cb_data)
{
	const char *refname = cb_data;

	if (verbose)
		fprintf_ln(stderr, _("Checking reflog %s->%s"),
			   oid_to_hex(ooid), oid_to_hex(noid));

	fsck_handle_reflog_oid(refname, ooid, 0);
	fsck_handle_reflog_oid(refname, noid, timestamp);
	return 0;
}