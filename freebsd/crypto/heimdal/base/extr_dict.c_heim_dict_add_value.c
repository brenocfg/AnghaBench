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
struct hashentry {struct hashentry* next; struct hashentry** prev; void* value; void* key; } ;
typedef  int /*<<< orphan*/  heim_object_t ;
typedef  TYPE_1__* heim_dict_t ;
struct TYPE_4__ {unsigned long size; struct hashentry** tab; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct hashentry* _search (TYPE_1__*,int /*<<< orphan*/ ) ; 
 unsigned long heim_get_hash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heim_release (void*) ; 
 void* heim_retain (int /*<<< orphan*/ ) ; 
 struct hashentry* malloc (int) ; 

int
heim_dict_add_value(heim_dict_t dict, heim_object_t key, heim_object_t value)
{
    struct hashentry **tabptr, *h;

    h = _search(dict, key);
    if (h) {
	heim_release(h->value);
	h->value = heim_retain(value);
    } else {
	unsigned long v;

	h = malloc(sizeof(*h));
	if (h == NULL)
	    return ENOMEM;

	h->key = heim_retain(key);
	h->value = heim_retain(value);

	v = heim_get_hash(key);

	tabptr = &dict->tab[v % dict->size];
	h->next = *tabptr;
	*tabptr = h;
	h->prev = tabptr;
	if (h->next)
	    h->next->prev = &h->next;
    }

    return 0;
}