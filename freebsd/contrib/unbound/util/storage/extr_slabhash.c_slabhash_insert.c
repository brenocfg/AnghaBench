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
struct slabhash {int /*<<< orphan*/ * array; } ;
struct lruhash_entry {int dummy; } ;
typedef  int /*<<< orphan*/  hashvalue_type ;

/* Variables and functions */
 int /*<<< orphan*/  lruhash_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct lruhash_entry*,void*,void*) ; 
 size_t slab_idx (struct slabhash*,int /*<<< orphan*/ ) ; 

void slabhash_insert(struct slabhash* sl, hashvalue_type hash, 
	struct lruhash_entry* entry, void* data, void* arg)
{
	lruhash_insert(sl->array[slab_idx(sl, hash)], hash, entry, data, arg);
}