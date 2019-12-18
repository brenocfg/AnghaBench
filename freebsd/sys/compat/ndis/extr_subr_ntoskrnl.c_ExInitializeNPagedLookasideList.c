#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  slist_entry ;
struct TYPE_4__ {int gl_size; int /*<<< orphan*/  gl_maxdepth; int /*<<< orphan*/  gl_depth; int /*<<< orphan*/  gl_type; int /*<<< orphan*/ * gl_freefunc; int /*<<< orphan*/ * gl_allocfunc; int /*<<< orphan*/  gl_tag; } ;
struct TYPE_5__ {TYPE_1__ nll_l; int /*<<< orphan*/  nll_obsoletelock; } ;
typedef  TYPE_2__ npaged_lookaside_list ;
typedef  int /*<<< orphan*/  lookaside_free_func ;
typedef  int /*<<< orphan*/  lookaside_alloc_func ;
typedef  int /*<<< orphan*/  funcptr ;

/* Variables and functions */
 scalar_t__ ExAllocatePoolWithTag ; 
 scalar_t__ ExFreePool ; 
 int /*<<< orphan*/  KeInitializeSpinLock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOOKASIDE_DEPTH ; 
 int /*<<< orphan*/  NonPagedPool ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 void* ntoskrnl_findwrap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ExInitializeNPagedLookasideList(npaged_lookaside_list *lookaside,
	lookaside_alloc_func *allocfunc, lookaside_free_func *freefunc,
	uint32_t flags, size_t size, uint32_t tag, uint16_t depth)
{
	bzero((char *)lookaside, sizeof(npaged_lookaside_list));

	if (size < sizeof(slist_entry))
		lookaside->nll_l.gl_size = sizeof(slist_entry);
	else
		lookaside->nll_l.gl_size = size;
	lookaside->nll_l.gl_tag = tag;
	if (allocfunc == NULL)
		lookaside->nll_l.gl_allocfunc =
		    ntoskrnl_findwrap((funcptr)ExAllocatePoolWithTag);
	else
		lookaside->nll_l.gl_allocfunc = allocfunc;

	if (freefunc == NULL)
		lookaside->nll_l.gl_freefunc =
		    ntoskrnl_findwrap((funcptr)ExFreePool);
	else
		lookaside->nll_l.gl_freefunc = freefunc;

#ifdef __i386__
	KeInitializeSpinLock(&lookaside->nll_obsoletelock);
#endif

	lookaside->nll_l.gl_type = NonPagedPool;
	lookaside->nll_l.gl_depth = depth;
	lookaside->nll_l.gl_maxdepth = LOOKASIDE_DEPTH;
}