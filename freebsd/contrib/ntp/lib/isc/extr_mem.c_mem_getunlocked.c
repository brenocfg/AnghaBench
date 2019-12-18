#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {size_t max_size; unsigned int quota; size_t total; size_t inuse; TYPE_2__* stats; TYPE_1__** freelists; int /*<<< orphan*/  memalloc_failures; int /*<<< orphan*/  arg; void* (* memalloc ) (int /*<<< orphan*/ ,size_t) ;} ;
typedef  TYPE_3__ isc__mem_t ;
struct TYPE_7__ {int /*<<< orphan*/  freefrags; int /*<<< orphan*/  totalgets; int /*<<< orphan*/  gets; } ;
struct TYPE_6__ {struct TYPE_6__* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (void*,int,size_t) ; 
 int /*<<< orphan*/  more_frags (TYPE_3__*,size_t) ; 
 size_t quantize (size_t) ; 
 void* stub1 (int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static inline void *
mem_getunlocked(isc__mem_t *ctx, size_t size) {
	size_t new_size = quantize(size);
	void *ret;

	if (size >= ctx->max_size || new_size >= ctx->max_size) {
		/*
		 * memget() was called on something beyond our upper limit.
		 */
		if (ctx->quota != 0U && ctx->total + size > ctx->quota) {
			ret = NULL;
			goto done;
		}
		ret = (ctx->memalloc)(ctx->arg, size);
		if (ret == NULL) {
			ctx->memalloc_failures++;
			goto done;
		}
		ctx->total += size;
		ctx->inuse += size;
		ctx->stats[ctx->max_size].gets++;
		ctx->stats[ctx->max_size].totalgets++;
		/*
		 * If we don't set new_size to size, then the
		 * ISC_MEM_FILL code might write over bytes we
		 * don't own.
		 */
		new_size = size;
		goto done;
	}

	/*
	 * If there are no blocks in the free list for this size, get a chunk
	 * of memory and then break it up into "new_size"-sized blocks, adding
	 * them to the free list.
	 */
	if (ctx->freelists[new_size] == NULL && !more_frags(ctx, new_size))
		return (NULL);

	/*
	 * The free list uses the "rounded-up" size "new_size".
	 */
	ret = ctx->freelists[new_size];
	ctx->freelists[new_size] = ctx->freelists[new_size]->next;

	/*
	 * The stats[] uses the _actual_ "size" requested by the
	 * caller, with the caveat (in the code above) that "size" >= the
	 * max. size (max_size) ends up getting recorded as a call to
	 * max_size.
	 */
	ctx->stats[size].gets++;
	ctx->stats[size].totalgets++;
	ctx->stats[new_size].freefrags--;
	ctx->inuse += new_size;

 done:

#if ISC_MEM_FILL
	if (ret != NULL)
		memset(ret, 0xbe, new_size); /* Mnemonic for "beef". */
#endif

	return (ret);
}