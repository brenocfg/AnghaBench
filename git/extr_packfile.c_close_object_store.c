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
struct raw_object_store {int /*<<< orphan*/ * multi_pack_index; struct packed_git* packed_git; } ;
struct packed_git {scalar_t__ do_not_close; struct packed_git* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 int /*<<< orphan*/  close_commit_graph (struct raw_object_store*) ; 
 int /*<<< orphan*/  close_midx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close_pack (struct packed_git*) ; 

void close_object_store(struct raw_object_store *o)
{
	struct packed_git *p;

	for (p = o->packed_git; p; p = p->next)
		if (p->do_not_close)
			BUG("want to close pack marked 'do-not-close'");
		else
			close_pack(p);

	if (o->multi_pack_index) {
		close_midx(o->multi_pack_index);
		o->multi_pack_index = NULL;
	}

	close_commit_graph(o);
}