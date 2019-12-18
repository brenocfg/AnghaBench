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
struct lruhash_entry {int /*<<< orphan*/  key; void* data; struct lruhash_entry* overflow_next; } ;
struct lruhash_bin {struct lruhash_entry* overflow_list; int /*<<< orphan*/  lock; } ;
struct lruhash {int /*<<< orphan*/  cb_arg; int /*<<< orphan*/  (* deldatafunc ) (void*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* delkeyfunc ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  lock_quick_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (void*,int /*<<< orphan*/ ) ; 

void 
bin_delete(struct lruhash* table, struct lruhash_bin* bin)
{
	struct lruhash_entry* p, *np;
	void *d;
	if(!bin)
		return;
	lock_quick_destroy(&bin->lock);
	p = bin->overflow_list;
	bin->overflow_list = NULL;
	while(p) {
		np = p->overflow_next;
		d = p->data;
		(*table->delkeyfunc)(p->key, table->cb_arg);
		(*table->deldatafunc)(d, table->cb_arg);
		p = np;
	}
}