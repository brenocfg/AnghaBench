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
struct ohash_info {int /*<<< orphan*/  data; int /*<<< orphan*/  alloc; int /*<<< orphan*/  free; int /*<<< orphan*/  (* calloc ) (unsigned long,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  key_offset; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; int /*<<< orphan*/  (* calloc ) (unsigned long,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  alloc; int /*<<< orphan*/  free; int /*<<< orphan*/  key_offset; } ;
struct ohash {unsigned long size; scalar_t__ deleted; scalar_t__ total; TYPE_1__ info; int /*<<< orphan*/  t; } ;
struct _ohash_record {int dummy; } ;

/* Variables and functions */
 unsigned long MINSIZE ; 
 int /*<<< orphan*/  STAT_HASH_CREATION ; 
 unsigned long STAT_HASH_SIZE ; 
 int /*<<< orphan*/  stub1 (unsigned long,int,int /*<<< orphan*/ ) ; 

void
ohash_init(struct ohash *h, unsigned int size, struct ohash_info *info)
{
	h->size = 1UL << size;
	if (h->size < MINSIZE)
		h->size = MINSIZE;
#ifdef STATS_HASH
	STAT_HASH_CREATION++;
	STAT_HASH_SIZE += h->size;
#endif
	/* Copy info so that caller may free it.  */
	h->info.key_offset = info->key_offset;
	h->info.calloc = info->calloc;
	h->info.free = info->free;
	h->info.alloc = info->alloc;
	h->info.data = info->data;
	h->t = (h->info.calloc)(h->size, sizeof(struct _ohash_record),
		    h->info.data);
	h->total = h->deleted = 0;
}