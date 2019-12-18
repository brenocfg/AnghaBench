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
struct spanhash_top {int alloc_log2; int /*<<< orphan*/  free; struct spanhash* data; } ;
struct spanhash {int hashval; scalar_t__ cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  INITIAL_FREE (int) ; 
 int /*<<< orphan*/  free (struct spanhash_top*) ; 
 int /*<<< orphan*/  memset (struct spanhash*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  st_add (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  st_mult (int,int) ; 
 struct spanhash_top* xmalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct spanhash_top *spanhash_rehash(struct spanhash_top *orig)
{
	struct spanhash_top *new_spanhash;
	int i;
	int osz = 1 << orig->alloc_log2;
	int sz = osz << 1;

	new_spanhash = xmalloc(st_add(sizeof(*orig),
			     st_mult(sizeof(struct spanhash), sz)));
	new_spanhash->alloc_log2 = orig->alloc_log2 + 1;
	new_spanhash->free = INITIAL_FREE(new_spanhash->alloc_log2);
	memset(new_spanhash->data, 0, sizeof(struct spanhash) * sz);
	for (i = 0; i < osz; i++) {
		struct spanhash *o = &(orig->data[i]);
		int bucket;
		if (!o->cnt)
			continue;
		bucket = o->hashval & (sz - 1);
		while (1) {
			struct spanhash *h = &(new_spanhash->data[bucket++]);
			if (!h->cnt) {
				h->hashval = o->hashval;
				h->cnt = o->cnt;
				new_spanhash->free--;
				break;
			}
			if (sz <= bucket)
				bucket = 0;
		}
	}
	free(orig);
	return new_spanhash;
}