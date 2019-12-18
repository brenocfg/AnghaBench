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
typedef  size_t u_int32_t ;
struct member_entry {struct member_entry* next; struct grouplist* groups; int /*<<< orphan*/  key; } ;
struct grouplist {int groupid; struct grouplist* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  dummy ; 
 size_t hashkey (char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strdup (char*) ; 

void mstore (struct member_entry *table[], char *key, int gid, int dup)
{
	struct member_entry *cur, *new;
	struct grouplist *tmp;
	u_int32_t i;

	i = hashkey(key);
	cur = table[i];

	if (!dup) {
		tmp = (struct grouplist *)malloc(sizeof(struct grouplist));
		tmp->groupid = gid;
		tmp->next = NULL;
	}

		/* Check if all we have to do is insert a new groupname. */
	while (cur) {
		if (!dup && !strcmp(cur->key, key)) {
			tmp->next = cur->groups;
			cur->groups = tmp;
			return;
		}
		cur = cur->next;
	}

	/* Didn't find a match -- add the whole mess to the table. */
	new = (struct member_entry *)malloc(sizeof(struct member_entry));
	new->key = strdup(key);
	if (!dup)
		new->groups = tmp;
	else
		new->groups = (struct grouplist *)&dummy;
	new->next = table[i];
	table[i] = new;

	return;
}