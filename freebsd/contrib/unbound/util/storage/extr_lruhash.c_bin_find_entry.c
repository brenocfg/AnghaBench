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
struct lruhash_entry {scalar_t__ hash; struct lruhash_entry* overflow_next; int /*<<< orphan*/  key; } ;
struct lruhash_bin {struct lruhash_entry* overflow_list; } ;
struct lruhash {scalar_t__ (* compfunc ) (int /*<<< orphan*/ ,void*) ;} ;
typedef  scalar_t__ hashvalue_type ;

/* Variables and functions */
 scalar_t__ stub1 (int /*<<< orphan*/ ,void*) ; 

struct lruhash_entry* 
bin_find_entry(struct lruhash* table, 
	struct lruhash_bin* bin, hashvalue_type hash, void* key)
{
	struct lruhash_entry* p = bin->overflow_list;
	while(p) {
		if(p->hash == hash && table->compfunc(p->key, key) == 0)
			return p;
		p = p->overflow_next;
	}
	return NULL;
}