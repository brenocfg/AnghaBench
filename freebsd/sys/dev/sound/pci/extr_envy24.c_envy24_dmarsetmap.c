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
struct sc_info {unsigned long raddr; unsigned long rmap; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {unsigned long ds_addr; scalar_t__ ds_len; } ;
typedef  TYPE_1__ bus_dma_segment_t ;

/* Variables and functions */
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*,unsigned long,unsigned long) ; 

__attribute__((used)) static void
envy24_dmarsetmap(void *arg, bus_dma_segment_t *segs, int nseg, int error)
{
	struct sc_info *sc = (struct sc_info *)arg;

	sc->raddr = segs->ds_addr;
#if(0)
	device_printf(sc->dev, "envy24_dmarsetmap()\n");
	if (bootverbose) {
		printf("envy24(record): setmap %lx, %lx; ",
		    (unsigned long)segs->ds_addr,
		    (unsigned long)segs->ds_len);
		printf("%p -> %lx\n", sc->rmap, sc->raddr);
	}
#endif
}