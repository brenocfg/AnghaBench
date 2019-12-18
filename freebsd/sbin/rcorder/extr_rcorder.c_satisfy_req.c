#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ in_progress; TYPE_1__* next; } ;
typedef  TYPE_2__ provnode ;
struct TYPE_8__ {int /*<<< orphan*/ * entry; } ;
typedef  TYPE_3__ f_reqnode ;
struct TYPE_6__ {int /*<<< orphan*/  fnode; } ;
typedef  int /*<<< orphan*/  Hash_Entry ;

/* Variables and functions */
 int /*<<< orphan*/  Hash_GetKey (int /*<<< orphan*/ *) ; 
 TYPE_2__* Hash_GetValue (int /*<<< orphan*/ *) ; 
 scalar_t__ SET ; 
 int /*<<< orphan*/  do_file (int /*<<< orphan*/ ) ; 
 int exit_code ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
satisfy_req(f_reqnode *rnode, char *filename)
{
	Hash_Entry *entry;
	provnode *head;

	entry = rnode->entry;
	head = Hash_GetValue(entry);

	if (head == NULL) {
		warnx("requirement `%s' in file `%s' has no providers.",
		    Hash_GetKey(entry), filename);
		exit_code = 1;
		return;
	}

	/* return if the requirement is already satisfied. */
	if (head->next == NULL)
		return;

	/* 
	 * if list is marked as in progress,
	 *	print that there is a circular dependency on it and abort
	 */
	if (head->in_progress == SET) {
		warnx("Circular dependency on provision `%s' in file `%s'.",
		    Hash_GetKey(entry), filename);
		exit_code = 1;
		return;
	}

	head->in_progress = SET;
	
	/*
	 * while provision_list is not empty
	 *	do_file(first_member_of(provision_list));
	 */
	while (head->next != NULL)
		do_file(head->next->fnode);
}