#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct Hash_Entry {unsigned int namehash; int /*<<< orphan*/  name; int /*<<< orphan*/ * clientData; struct Hash_Entry* next; } ;
struct TYPE_4__ {unsigned int mask; int numEntries; int size; struct Hash_Entry** bucketPtr; } ;
typedef  TYPE_1__ Hash_Table ;
typedef  struct Hash_Entry Hash_Entry ;
typedef  int /*<<< orphan*/  Boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  RebuildTable (TYPE_1__*) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ emalloc (int) ; 
 int rebuildLimit ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

Hash_Entry *
Hash_CreateEntry(
	register Hash_Table *t,	/* Hash table to search. */
	char *key,		/* A hash key. */
	Boolean *newPtr)	/* Filled in with TRUE if new entry created,
				 * FALSE otherwise. */
{
	register Hash_Entry *e;
	register unsigned h;
	register char *p;
	int keylen;
	struct Hash_Entry **hp;

	/*
	 * Hash the key.  As a side effect, save the length (strlen) of the
	 * key in case we need to create the entry.
	 */
	for (h = 0, p = key; *p;)
		h = (h << 5) - h + *p++;
	keylen = p - key;
	p = key;
	for (e = t->bucketPtr[h & t->mask]; e != NULL; e = e->next) {
		if (e->namehash == h && strcmp(e->name, p) == 0) {
			if (newPtr != NULL)
				*newPtr = FALSE;
			return (e);
		}
	}

	/*
	 * The desired entry isn't there.  Before allocating a new entry,
	 * expand the table if necessary (and this changes the resulting
	 * bucket chain).
	 */
	if (t->numEntries >= rebuildLimit * t->size)
		RebuildTable(t);
	e = (Hash_Entry *) emalloc(sizeof(*e) + keylen);
	hp = &t->bucketPtr[h & t->mask];
	e->next = *hp;
	*hp = e;
	e->clientData = NULL;
	e->namehash = h;
	(void) strcpy(e->name, p);
	t->numEntries++;

	if (newPtr != NULL)
		*newPtr = TRUE;
	return (e);
}