#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* last; struct TYPE_7__* next; TYPE_2__* fnode; void* in_progress; void* head; } ;
typedef  TYPE_1__ provnode ;
struct TYPE_8__ {TYPE_3__* prov_list; int /*<<< orphan*/  filename; } ;
typedef  TYPE_2__ filenode ;
struct TYPE_9__ {struct TYPE_9__* next; TYPE_1__* pnode; } ;
typedef  TYPE_3__ f_provnode ;
typedef  int /*<<< orphan*/  Hash_Entry ;

/* Variables and functions */
 int /*<<< orphan*/ * Hash_CreateEntry (int /*<<< orphan*/ ,char*,int*) ; 
 TYPE_1__* Hash_GetValue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Hash_SetValue (int /*<<< orphan*/ *,TYPE_1__*) ; 
 void* RESET ; 
 void* SET ; 
 void* emalloc (int) ; 
 int /*<<< orphan*/  provide_hash ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void
add_provide(filenode *fnode, char *s)
{
	Hash_Entry *entry;
	f_provnode *f_pnode;
	provnode *pnode, *head;
	int new;

	entry = Hash_CreateEntry(provide_hash, s, &new);
	head = Hash_GetValue(entry);

	/* create a head node if necessary. */
	if (head == NULL) {
		head = emalloc(sizeof(*head));
		head->head = SET;
		head->in_progress = RESET;
		head->fnode = NULL;
		head->last = head->next = NULL;
		Hash_SetValue(entry, head);
	}
#if 0
	/*
	 * Don't warn about this.  We want to be able to support
	 * scripts that do two complex things:
	 *
	 *	- Two independent scripts which both provide the
	 *	  same thing.  Both scripts must be executed in
	 *	  any order to meet the barrier.  An example:
	 *
	 *		Script 1:
	 *
	 *			PROVIDE: mail
	 *			REQUIRE: LOGIN
	 *
	 *		Script 2:
	 *
	 *			PROVIDE: mail
	 *			REQUIRE: LOGIN
	 *
	 * 	- Two interdependent scripts which both provide the
	 *	  same thing.  Both scripts must be executed in
	 *	  graph order to meet the barrier.  An example:
	 *
	 *		Script 1:
	 *
	 *			PROVIDE: nameservice dnscache
	 *			REQUIRE: SERVERS
	 *
	 *		Script 2:
	 *
	 *			PROVIDE: nameservice nscd
	 *			REQUIRE: dnscache
	 */
	else if (new == 0) {
		warnx("file `%s' provides `%s'.", fnode->filename, s);
		warnx("\tpreviously seen in `%s'.",
		    head->next->fnode->filename);
	}
#endif

	pnode = emalloc(sizeof(*pnode));
	pnode->head = RESET;
	pnode->in_progress = RESET;
	pnode->fnode = fnode;
	pnode->next = head->next;
	pnode->last = head;
	head->next = pnode;
	if (pnode->next != NULL)
		pnode->next->last = pnode;

	f_pnode = emalloc(sizeof(*f_pnode));
	f_pnode->pnode = pnode;
	f_pnode->next = fnode->prov_list;
	fnode->prov_list = f_pnode;
}