#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
struct TYPE_3__ {scalar_t__ npages; scalar_t__ pos; scalar_t__ cnt; } ;
struct TYPE_4__ {int /*<<< orphan*/ * buffer; scalar_t__ size; } ;
struct pipe {TYPE_1__ pipe_map; TYPE_2__ pipe_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  PIPE_MTX (struct pipe*) ; 
 int /*<<< orphan*/  amountpipekva ; 
 int /*<<< orphan*/  atomic_subtract_long (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  mtx_owned (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pipe_map ; 
 int /*<<< orphan*/  vm_map_remove (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
pipe_free_kmem(struct pipe *cpipe)
{

	KASSERT(!mtx_owned(PIPE_MTX(cpipe)),
	    ("pipe_free_kmem: pipe mutex locked"));

	if (cpipe->pipe_buffer.buffer != NULL) {
		atomic_subtract_long(&amountpipekva, cpipe->pipe_buffer.size);
		vm_map_remove(pipe_map,
		    (vm_offset_t)cpipe->pipe_buffer.buffer,
		    (vm_offset_t)cpipe->pipe_buffer.buffer + cpipe->pipe_buffer.size);
		cpipe->pipe_buffer.buffer = NULL;
	}
#ifndef PIPE_NODIRECT
	{
		cpipe->pipe_map.cnt = 0;
		cpipe->pipe_map.pos = 0;
		cpipe->pipe_map.npages = 0;
	}
#endif
}