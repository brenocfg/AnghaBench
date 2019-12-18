#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hashentry {TYPE_1__** prev; TYPE_1__* next; int /*<<< orphan*/  value; int /*<<< orphan*/  key; } ;
typedef  int /*<<< orphan*/  heim_object_t ;
typedef  int /*<<< orphan*/  heim_dict_t ;
struct TYPE_2__ {struct TYPE_2__** prev; } ;

/* Variables and functions */
 struct hashentry* _search (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct hashentry*) ; 
 int /*<<< orphan*/  heim_release (int /*<<< orphan*/ ) ; 

void
heim_dict_delete_key(heim_dict_t dict, heim_object_t key)
{
    struct hashentry *h = _search(dict, key);

    if (h == NULL)
	return;

    heim_release(h->key);
    heim_release(h->value);

    if ((*(h->prev) = h->next) != NULL)
	h->next->prev = h->prev;

    free(h);
}