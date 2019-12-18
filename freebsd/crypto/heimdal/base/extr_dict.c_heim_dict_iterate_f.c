#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hashentry {int /*<<< orphan*/  value; int /*<<< orphan*/  key; struct hashentry* next; } ;
typedef  TYPE_1__* heim_dict_t ;
typedef  int /*<<< orphan*/  (* heim_dict_iterator_f_t ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ;
struct TYPE_3__ {size_t size; struct hashentry** tab; } ;

/* Variables and functions */

void
heim_dict_iterate_f(heim_dict_t dict, heim_dict_iterator_f_t func, void *arg)
{
    struct hashentry **h, *g;

    for (h = dict->tab; h < &dict->tab[dict->size]; ++h)
	for (g = *h; g; g = g->next)
	    func(g->key, g->value, arg);
}