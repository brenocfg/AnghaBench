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
struct entry {struct entry* e_next; int /*<<< orphan*/ * e_entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  badentry (struct entry*,char*) ; 
 int /*<<< orphan*/  freeentry (struct entry*) ; 
 struct entry* removelist ; 
 int /*<<< orphan*/  removenode (struct entry*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  vprintf (int /*<<< orphan*/ ,char*) ; 

void
removeoldnodes(void)
{
	struct entry *ep, **prev;
	long change;

	vprintf(stdout, "Remove old nodes (directories).\n");
	do	{
		change = 0;
		prev = &removelist;
		for (ep = removelist; ep != NULL; ep = *prev) {
			if (ep->e_entries != NULL) {
				prev = &ep->e_next;
				continue;
			}
			*prev = ep->e_next;
			removenode(ep);
			freeentry(ep);
			change++;
		}
	} while (change);
	for (ep = removelist; ep != NULL; ep = ep->e_next)
		badentry(ep, "cannot remove, non-empty");
}