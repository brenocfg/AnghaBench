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
 int /*<<< orphan*/  handle_one_reflog_commit (struct object_id*,void*) ; 

__attribute__((used)) static int handle_one_reflog_ent(struct object_id *ooid, struct object_id *noid,
		const char *email, timestamp_t timestamp, int tz,
		const char *message, void *cb_data)
{
	handle_one_reflog_commit(ooid, cb_data);
	handle_one_reflog_commit(noid, cb_data);
	return 0;
}