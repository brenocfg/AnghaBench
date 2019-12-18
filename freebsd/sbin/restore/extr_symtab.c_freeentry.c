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
struct entry {scalar_t__ e_flags; scalar_t__ e_type; scalar_t__ e_ino; struct entry* e_next; int /*<<< orphan*/  e_name; struct entry* e_links; int /*<<< orphan*/ * e_entries; } ;
typedef  scalar_t__ ino_t ;

/* Variables and functions */
 scalar_t__ NODE ; 
 scalar_t__ REMOVED ; 
 int /*<<< orphan*/  addino (scalar_t__,struct entry*) ; 
 int /*<<< orphan*/  badentry (struct entry*,char*) ; 
 int /*<<< orphan*/  deleteino (scalar_t__) ; 
 struct entry* freelist ; 
 int /*<<< orphan*/  freename (int /*<<< orphan*/ ) ; 
 struct entry* lookupino (scalar_t__) ; 
 int /*<<< orphan*/  removeentry (struct entry*) ; 

void
freeentry(struct entry *ep)
{
	struct entry *np;
	ino_t inum;

	if (ep->e_flags != REMOVED)
		badentry(ep, "not marked REMOVED");
	if (ep->e_type == NODE) {
		if (ep->e_links != NULL)
			badentry(ep, "freeing referenced directory");
		if (ep->e_entries != NULL)
			badentry(ep, "freeing non-empty directory");
	}
	if (ep->e_ino != 0) {
		np = lookupino(ep->e_ino);
		if (np == NULL)
			badentry(ep, "lookupino failed");
		if (np == ep) {
			inum = ep->e_ino;
			deleteino(inum);
			if (ep->e_links != NULL)
				addino(inum, ep->e_links);
		} else {
			for (; np != NULL; np = np->e_links) {
				if (np->e_links == ep) {
					np->e_links = ep->e_links;
					break;
				}
			}
			if (np == NULL)
				badentry(ep, "link not found");
		}
	}
	removeentry(ep);
	freename(ep->e_name);
	ep->e_next = freelist;
	freelist = ep;
}