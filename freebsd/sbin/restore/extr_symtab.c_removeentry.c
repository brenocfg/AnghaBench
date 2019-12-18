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
struct entry {struct entry* e_sibling; struct entry* e_entries; struct entry* e_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  badentry (struct entry*,char*) ; 

__attribute__((used)) static void
removeentry(struct entry *ep)
{
	struct entry *np;

	np = ep->e_parent;
	if (np->e_entries == ep) {
		np->e_entries = ep->e_sibling;
	} else {
		for (np = np->e_entries; np != NULL; np = np->e_sibling) {
			if (np->e_sibling == ep) {
				np->e_sibling = ep->e_sibling;
				break;
			}
		}
		if (np == NULL)
			badentry(ep, "cannot find entry in parent list");
	}
}