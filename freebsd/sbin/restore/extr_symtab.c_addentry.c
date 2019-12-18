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
struct entry {int e_type; char* e_name; struct entry* e_links; scalar_t__ e_ino; struct entry* e_entries; struct entry* e_sibling; struct entry* e_parent; void* e_namlen; struct entry* e_next; } ;
typedef  scalar_t__ ino_t ;

/* Variables and functions */
 int LINK ; 
 scalar_t__ UFS_ROOTINO ; 
 int /*<<< orphan*/  addino (scalar_t__,struct entry*) ; 
 scalar_t__ calloc (int,int) ; 
 struct entry* freelist ; 
 struct entry* lookupino (scalar_t__) ; 
 struct entry* lookupparent (char*) ; 
 int /*<<< orphan*/  memset (struct entry*,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  panic (char*,...) ; 
 void* savename (char*) ; 
 void* strlen (char*) ; 
 char* strrchr (char*,char) ; 

struct entry *
addentry(char *name, ino_t inum, int type)
{
	struct entry *np, *ep;

	if (freelist != NULL) {
		np = freelist;
		freelist = np->e_next;
		memset(np, 0, (long)sizeof(struct entry));
	} else {
		np = (struct entry *)calloc(1, sizeof(struct entry));
		if (np == NULL)
			panic("no memory to extend symbol table\n");
	}
	np->e_type = type & ~LINK;
	ep = lookupparent(name);
	if (ep == NULL) {
		if (inum != UFS_ROOTINO || lookupino(UFS_ROOTINO) != NULL)
			panic("bad name to addentry %s\n", name);
		np->e_name = savename(name);
		np->e_namlen = strlen(name);
		np->e_parent = np;
		addino(UFS_ROOTINO, np);
		return (np);
	}
	np->e_name = savename(strrchr(name, '/') + 1);
	np->e_namlen = strlen(np->e_name);
	np->e_parent = ep;
	np->e_sibling = ep->e_entries;
	ep->e_entries = np;
	if (type & LINK) {
		ep = lookupino(inum);
		if (ep == NULL)
			panic("link to non-existent name\n");
		np->e_ino = inum;
		np->e_links = ep->e_links;
		ep->e_links = np;
	} else if (inum != 0) {
		if (lookupino(inum) != NULL)
			panic("duplicate entry\n");
		addino(inum, np);
	}
	return (np);
}