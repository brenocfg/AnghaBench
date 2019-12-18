#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t max_size; size_t total; size_t inuse; TYPE_1__* stats; TYPE_3__** freelists; int /*<<< orphan*/  arg; int /*<<< orphan*/  (* memfree ) (int /*<<< orphan*/ ,void*) ;} ;
typedef  TYPE_2__ isc__mem_t ;
struct TYPE_7__ {struct TYPE_7__* next; } ;
typedef  TYPE_3__ element ;
struct TYPE_5__ {unsigned int gets; int /*<<< orphan*/  freefrags; } ;

/* Variables and functions */
 int /*<<< orphan*/  INSIST (int) ; 
 int /*<<< orphan*/  check_overrun (void*,size_t,size_t) ; 
 int /*<<< orphan*/  memset (void*,int,size_t) ; 
 size_t quantize (size_t) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static inline void
mem_putunlocked(isc__mem_t *ctx, void *mem, size_t size) {
	size_t new_size = quantize(size);

	if (size == ctx->max_size || new_size >= ctx->max_size) {
		/*
		 * memput() called on something beyond our upper limit.
		 */
#if ISC_MEM_FILL
		memset(mem, 0xde, size); /* Mnemonic for "dead". */
#endif
		(ctx->memfree)(ctx->arg, mem);
		INSIST(ctx->stats[ctx->max_size].gets != 0U);
		ctx->stats[ctx->max_size].gets--;
		INSIST(size <= ctx->total);
		ctx->inuse -= size;
		ctx->total -= size;
		return;
	}

#if ISC_MEM_FILL
#if ISC_MEM_CHECKOVERRUN
	check_overrun(mem, size, new_size);
#endif
	memset(mem, 0xde, new_size); /* Mnemonic for "dead". */
#endif

	/*
	 * The free list uses the "rounded-up" size "new_size".
	 */
	((element *)mem)->next = ctx->freelists[new_size];
	ctx->freelists[new_size] = (element *)mem;

	/*
	 * The stats[] uses the _actual_ "size" requested by the
	 * caller, with the caveat (in the code above) that "size" >= the
	 * max. size (max_size) ends up getting recorded as a call to
	 * max_size.
	 */
	INSIST(ctx->stats[size].gets != 0U);
	ctx->stats[size].gets--;
	ctx->stats[new_size].freefrags++;
	ctx->inuse -= new_size;
}