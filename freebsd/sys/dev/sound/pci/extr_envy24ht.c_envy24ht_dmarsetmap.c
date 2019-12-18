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
typedef  int /*<<< orphan*/  uint32_t ;
struct sc_info {int /*<<< orphan*/  dev; scalar_t__ raddr; } ;
struct TYPE_3__ {int ds_len; scalar_t__ ds_addr; } ;
typedef  TYPE_1__ bus_dma_segment_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENVY24HT_MT_RADDR ; 
 int /*<<< orphan*/  ENVY24HT_MT_RCNT ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  envy24ht_wrmt (struct sc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,unsigned long,unsigned long) ; 

__attribute__((used)) static void
envy24ht_dmarsetmap(void *arg, bus_dma_segment_t *segs, int nseg, int error)
{
	struct sc_info *sc = arg;

	sc->raddr = segs->ds_addr;
#if(0)
	device_printf(sc->dev, "envy24ht_dmarsetmap()\n");
	if (bootverbose) {
		printf("envy24ht(record): setmap %lx, %lx; ",
		    (unsigned long)segs->ds_addr,
		    (unsigned long)segs->ds_len);
	}
#endif
	envy24ht_wrmt(sc, ENVY24HT_MT_RADDR, (uint32_t)segs->ds_addr, 4);
	envy24ht_wrmt(sc, ENVY24HT_MT_RCNT, (uint32_t)(segs->ds_len / 4 - 1), 2);
}