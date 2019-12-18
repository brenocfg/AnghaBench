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
struct group_entry {char* data; struct group_entry* next; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 size_t hashkey (char*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

char *
lookup(struct group_entry *table[], char *key)
{
	struct group_entry *cur;

	cur = table[hashkey(key)];

	while (cur) {
		if (!strcmp(cur->key, key))
			return(cur->data);
		cur = cur->next;
	}

	return(NULL);
}