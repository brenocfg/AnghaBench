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
struct slabhash {size_t size; int /*<<< orphan*/ * array; } ;

/* Variables and functions */
 int /*<<< orphan*/  lruhash_traverse (int /*<<< orphan*/ ,int,void (*) (struct lruhash_entry*,void*),void*) ; 

void slabhash_traverse(struct slabhash* sh, int wr,
	void (*func)(struct lruhash_entry*, void*), void* arg)
{
	size_t i;
	for(i=0; i<sh->size; i++)
		lruhash_traverse(sh->array[i], wr, func, arg);
}