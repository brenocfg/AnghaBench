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
struct TYPE_3__ {int /*<<< orphan*/  arg; int /*<<< orphan*/  (* memfree ) (int /*<<< orphan*/ ,void*) ;} ;
typedef  TYPE_1__ isc__mem_t ;

/* Variables and functions */
 int /*<<< orphan*/  INSIST (int) ; 
 int /*<<< orphan*/  UNUSED (size_t) ; 
 int /*<<< orphan*/  memset (void*,int,size_t) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static inline void
mem_put(isc__mem_t *ctx, void *mem, size_t size) {
#if ISC_MEM_CHECKOVERRUN
	INSIST(((unsigned char *)mem)[size] == 0xbe);
#endif
#if ISC_MEM_FILL
	memset(mem, 0xde, size); /* Mnemonic for "dead". */
#else
	UNUSED(size);
#endif
	(ctx->memfree)(ctx->arg, mem);
}