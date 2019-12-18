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
struct ref_store {int dummy; } ;
struct read_ref_at_cb {char const* refname; int cnt; char** msg; int* cutoff_tz; int* cutoff_cnt; scalar_t__ found_it; int /*<<< orphan*/  reccnt; struct object_id* oid; int /*<<< orphan*/ * cutoff_time; int /*<<< orphan*/  at_time; } ;
struct object_id {int dummy; } ;
typedef  int /*<<< orphan*/  cb ;

/* Variables and functions */
 unsigned int GET_OID_QUIETLY ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  memset (struct read_ref_at_cb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  read_ref_at_ent ; 
 int /*<<< orphan*/  read_ref_at_ent_oldest ; 
 int /*<<< orphan*/  refs_for_each_reflog_ent (struct ref_store*,char const*,int /*<<< orphan*/ ,struct read_ref_at_cb*) ; 
 int /*<<< orphan*/  refs_for_each_reflog_ent_reverse (struct ref_store*,char const*,int /*<<< orphan*/ ,struct read_ref_at_cb*) ; 

int read_ref_at(struct ref_store *refs, const char *refname,
		unsigned int flags, timestamp_t at_time, int cnt,
		struct object_id *oid, char **msg,
		timestamp_t *cutoff_time, int *cutoff_tz, int *cutoff_cnt)
{
	struct read_ref_at_cb cb;

	memset(&cb, 0, sizeof(cb));
	cb.refname = refname;
	cb.at_time = at_time;
	cb.cnt = cnt;
	cb.msg = msg;
	cb.cutoff_time = cutoff_time;
	cb.cutoff_tz = cutoff_tz;
	cb.cutoff_cnt = cutoff_cnt;
	cb.oid = oid;

	refs_for_each_reflog_ent_reverse(refs, refname, read_ref_at_ent, &cb);

	if (!cb.reccnt) {
		if (flags & GET_OID_QUIETLY)
			exit(128);
		else
			die(_("log for %s is empty"), refname);
	}
	if (cb.found_it)
		return 0;

	refs_for_each_reflog_ent(refs, refname, read_ref_at_ent_oldest, &cb);

	return 1;
}