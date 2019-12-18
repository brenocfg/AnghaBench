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
struct dosDirEntry {struct dosDirEntry* parent; struct dosDirEntry* next; struct dosDirEntry* child; } ;
struct dirTodoNode {struct dirTodoNode* next; } ;

/* Variables and functions */
 int /*<<< orphan*/ * buffer ; 
 int /*<<< orphan*/ * delbuf ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  freeDirTodo (struct dirTodoNode*) ; 
 int /*<<< orphan*/  freeDosDirEntry (struct dosDirEntry*) ; 
 int /*<<< orphan*/ * lostDir ; 
 struct dirTodoNode* pendingDirectories ; 
 struct dosDirEntry* rootDir ; 

void
finishDosDirSection(void)
{
	struct dirTodoNode *p, *np;
	struct dosDirEntry *d, *nd;

	for (p = pendingDirectories; p; p = np) {
		np = p->next;
		freeDirTodo(p);
	}
	pendingDirectories = NULL;
	for (d = rootDir; d; d = nd) {
		if ((nd = d->child) != NULL) {
			d->child = 0;
			continue;
		}
		if (!(nd = d->next))
			nd = d->parent;
		freeDosDirEntry(d);
	}
	rootDir = lostDir = NULL;
	free(buffer);
	free(delbuf);
	buffer = NULL;
	delbuf = NULL;
}