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
struct data {int /*<<< orphan*/  non_common_revs; } ;
struct commit_list {struct commit* item; struct commit_list* next; } ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  parsed; } ;
struct commit {TYPE_1__ object; struct commit_list* parents; } ;

/* Variables and functions */
 int COMMON ; 
 int POPPED ; 
 int SEEN ; 

__attribute__((used)) static void mark_common(struct data *data, struct commit *c)
{
	struct commit_list *p;

	if (c->object.flags & COMMON)
		return;
	c->object.flags |= COMMON;
	if (!(c->object.flags & POPPED))
		data->non_common_revs--;

	if (!c->object.parsed)
		return;
	for (p = c->parents; p; p = p->next) {
		if (p->item->object.flags & SEEN)
			mark_common(data, p->item);
	}
}