#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_8__ {struct TYPE_8__* next; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ nvram_tuple_t ;
struct TYPE_9__ {TYPE_1__** nvram_hash; TYPE_1__* nvram_dead; } ;
typedef  TYPE_2__ nvram_handle_t ;

/* Variables and functions */
 size_t NVRAM_ARRAYSIZE (TYPE_1__**) ; 
 TYPE_1__* _nvram_realloc (TYPE_2__*,TYPE_1__*,char const*,char const*) ; 
 size_t hash (char const*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

int nvram_set(nvram_handle_t *h, const char *name, const char *value)
{
	uint32_t i;
	nvram_tuple_t *t, *u, **prev;

	/* Hash the name */
	i = hash(name) % NVRAM_ARRAYSIZE(h->nvram_hash);

	/* Find the associated tuple in the hash table */
	for (prev = &h->nvram_hash[i], t = *prev;
		 t && strcmp(t->name, name); prev = &t->next, t = *prev);

	/* (Re)allocate tuple */
	if (!(u = _nvram_realloc(h, t, name, value)))
		return -12; /* -ENOMEM */

	/* Value reallocated */
	if (t && t == u)
		return 0;

	/* Move old tuple to the dead table */
	if (t) {
		*prev = t->next;
		t->next = h->nvram_dead;
		h->nvram_dead = t;
	}

	/* Add new tuple to the hash table */
	u->next = h->nvram_hash[i];
	h->nvram_hash[i] = u;

	return 0;
}