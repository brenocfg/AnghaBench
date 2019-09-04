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
struct entry {struct commit* commit; } ;
struct data {int /*<<< orphan*/  non_common_revs; int /*<<< orphan*/  rev_list; } ;
struct TYPE_2__ {int flags; } ;
struct commit {TYPE_1__ object; } ;

/* Variables and functions */
 int COMMON ; 
 int SEEN ; 
 int /*<<< orphan*/  prio_queue_put (int /*<<< orphan*/ *,struct entry*) ; 
 struct entry* xcalloc (int,int) ; 

__attribute__((used)) static struct entry *rev_list_push(struct data *data, struct commit *commit, int mark)
{
	struct entry *entry;
	commit->object.flags |= mark | SEEN;

	entry = xcalloc(1, sizeof(*entry));
	entry->commit = commit;
	prio_queue_put(&data->rev_list, entry);

	if (!(mark & COMMON))
		data->non_common_revs++;
	return entry;
}