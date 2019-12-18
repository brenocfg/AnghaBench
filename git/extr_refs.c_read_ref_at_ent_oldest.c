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
struct read_ref_at_cb {int* cutoff_tz; int /*<<< orphan*/  oid; int /*<<< orphan*/  reccnt; int /*<<< orphan*/ * cutoff_cnt; int /*<<< orphan*/ * cutoff_time; int /*<<< orphan*/ * msg; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 scalar_t__ is_null_oid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ ,struct object_id*) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

__attribute__((used)) static int read_ref_at_ent_oldest(struct object_id *ooid, struct object_id *noid,
				  const char *email, timestamp_t timestamp,
				  int tz, const char *message, void *cb_data)
{
	struct read_ref_at_cb *cb = cb_data;

	if (cb->msg)
		*cb->msg = xstrdup(message);
	if (cb->cutoff_time)
		*cb->cutoff_time = timestamp;
	if (cb->cutoff_tz)
		*cb->cutoff_tz = tz;
	if (cb->cutoff_cnt)
		*cb->cutoff_cnt = cb->reccnt;
	oidcpy(cb->oid, ooid);
	if (is_null_oid(cb->oid))
		oidcpy(cb->oid, noid);
	/* We just want the first entry */
	return 1;
}