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
struct TYPE_3__ {scalar_t__ ds_len; scalar_t__ ds_addr; } ;
typedef  TYPE_1__ bus_dma_segment_t ;
typedef  int /*<<< orphan*/  bus_addr_t ;

/* Variables and functions */
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  printf (char*,unsigned long,unsigned long,int,int) ; 

__attribute__((used)) static void
emu_setmap(void *arg, bus_dma_segment_t *segs, int nseg, int error)
{
	bus_addr_t *phys = arg;

	*phys = error ? 0 : (bus_addr_t)segs->ds_addr;

	if (bootverbose) {
		printf("emu: setmap (%lx, %lx), nseg=%d, error=%d\n",
		    (unsigned long)segs->ds_addr, (unsigned long)segs->ds_len,
		    nseg, error);
	}
}