#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct process_commit_data {TYPE_1__* revs; TYPE_2__* dst; int /*<<< orphan*/  current_commit; int /*<<< orphan*/  looking_for; } ;
struct object {int /*<<< orphan*/  oid; } ;
struct TYPE_5__ {int /*<<< orphan*/  len; } ;
struct TYPE_4__ {int /*<<< orphan*/ * commits; } ;

/* Variables and functions */
 int /*<<< orphan*/  describe_commit (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  free_commit_list (int /*<<< orphan*/ *) ; 
 scalar_t__ oideq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_revision_walk () ; 
 int /*<<< orphan*/  strbuf_addf (TYPE_2__*,char*,char const*) ; 

__attribute__((used)) static void process_object(struct object *obj, const char *path, void *data)
{
	struct process_commit_data *pcd = data;

	if (oideq(&pcd->looking_for, &obj->oid) && !pcd->dst->len) {
		reset_revision_walk();
		describe_commit(&pcd->current_commit, pcd->dst);
		strbuf_addf(pcd->dst, ":%s", path);
		free_commit_list(pcd->revs->commits);
		pcd->revs->commits = NULL;
	}
}