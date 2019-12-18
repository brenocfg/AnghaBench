#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct TYPE_8__* prev; struct TYPE_8__* next; struct TYPE_8__* child; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ NODE ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ mtree_Sflag ; 
 int nodecmp (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  replacenode (TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
addchild(NODE *pathparent, NODE *centry)
{
	NODE *samename;      /* node with the same name as centry */
	NODE *replacepos;    /* if non-NULL, centry should replace this node */
	NODE *insertpos;     /* if non-NULL, centry should be inserted
			      * after this node */
	NODE *cur;           /* for stepping through the list */
	NODE *last;          /* the last node in the list */
	int cmp;

	samename = NULL;
	replacepos = NULL;
	insertpos = NULL;
	last = NULL;
	cur = pathparent->child;
	if (cur == NULL) {
		/* centry is pathparent's first and only child node so far */
		pathparent->child = centry;
		return;
	}

	/*
	 * pathparent already has at least one other child, so add the
	 * centry node to the list.
	 *
	 * We first scan through the list looking for an existing node
	 * with the same name (setting samename), and also looking
	 * for the correct position to replace or insert the new node
	 * (setting replacepos and/or insertpos).
	 */
	for (; cur != NULL; last = cur, cur = cur->next) {
		if (strcmp(centry->name, cur->name) == 0) {
			samename = cur;
		}
		if (mtree_Sflag) {
			cmp = nodecmp(centry, cur);
			if (cmp == 0) {
				replacepos = cur;
			} else if (cmp > 0) {
				insertpos = cur;
			}
		}
	}
	if (! mtree_Sflag) {
		if (samename != NULL) {
			/* replace node with same name */
			replacepos = samename;
		} else {
			/* add new node at end of list */
			insertpos = last;
		}
	}

	if (samename != NULL) {
		/*
		 * We found a node with the same name above.  Call
		 * replacenode(), which will either exit with an error,
		 * or replace the information in the samename node and
		 * free the information in the centry node.
		 */
		replacenode(samename, centry);
		if (samename == replacepos) {
			/* The just-replaced node was in the correct position */
			return;
		}
		if (samename == insertpos || samename->prev == insertpos) {
			/*
			 * We thought the new node should be just before
			 * or just after the replaced node, but that would
			 * be equivalent to just retaining the replaced node.
			 */
			return;
		}

		/*
		 * The just-replaced node is in the wrong position in
		 * the list.  This can happen if sort order depends on
		 * criteria other than the node name.
		 *
		 * Make centry point to the just-replaced node.	 Unlink
		 * the just-replaced node from the list, and allow it to
		 * be insterted in the correct position later.
		 */
		centry = samename;
		if (centry->prev)
			centry->prev->next = centry->next;
		else {
			/* centry->next is the new head of the list */
			pathparent->child = centry->next;
			assert(centry->next != NULL);
		}
		if (centry->next)
			centry->next->prev = centry->prev;
		centry->prev = NULL;
		centry->next = NULL;
	}

	if (insertpos == NULL) {
		/* insert centry at the beginning of the list */
		pathparent->child->prev = centry;
		centry->next = pathparent->child;
		centry->prev = NULL;
		pathparent->child = centry;
	} else {
		/* insert centry into the list just after insertpos */
		centry->next = insertpos->next;
		insertpos->next = centry;
		centry->prev = insertpos;
		if (centry->next)
			centry->next->prev = centry;
	}
	return;
}