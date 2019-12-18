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
struct TYPE_2__ {int /*<<< orphan*/  data; int /*<<< orphan*/  (* free ) (struct _ohash_record*,int /*<<< orphan*/ ) ;struct _ohash_record* (* calloc ) (size_t,int,int /*<<< orphan*/ ) ;} ;
struct ohash {int deleted; int total; unsigned int size; struct _ohash_record* t; TYPE_1__ info; } ;
struct _ohash_record {size_t hv; int /*<<< orphan*/ * p; } ;

/* Variables and functions */
 int /*<<< orphan*/ * DELETED ; 
 size_t MINSIZE ; 
 int /*<<< orphan*/  STAT_HASH_EXPAND ; 
 int /*<<< orphan*/  STAT_HASH_SIZE ; 
 unsigned int UINT_MAX ; 
 struct _ohash_record* stub1 (size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct _ohash_record*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ohash_resize(struct ohash *h)
{
	struct _ohash_record *n;
	size_t ns;
	unsigned int	j;
	unsigned int	i, incr;

	if (4 * h->deleted < h->total) {
		if (h->size >= (UINT_MAX >> 1U))
			ns = UINT_MAX;
		else
			ns = h->size << 1U;
	} else if (3 * h->deleted > 2 * h->total)
		ns = h->size >> 1U;
	else
		ns = h->size;
	if (ns < MINSIZE)
		ns = MINSIZE;
#ifdef STATS_HASH
	STAT_HASH_EXPAND++;
	STAT_HASH_SIZE += ns - h->size;
#endif

	n = (h->info.calloc)(ns, sizeof(struct _ohash_record), h->info.data);
	if (!n)
		return;

	for (j = 0; j < h->size; j++) {
		if (h->t[j].p != NULL && h->t[j].p != DELETED) {
			i = h->t[j].hv % ns;
			incr = ((h->t[j].hv % (ns - 2)) & ~1) + 1;
			while (n[i].p != NULL) {
				i += incr;
				if (i >= ns)
					i -= ns;
			}
			n[i].hv = h->t[j].hv;
			n[i].p = h->t[j].p;
		}
	}
	(h->info.free)(h->t, h->info.data);
	h->t = n;
	h->size = ns;
	h->total -= h->deleted;
	h->deleted = 0;
}