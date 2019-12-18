#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct sc_info {int /*<<< orphan*/  rbuf; int /*<<< orphan*/  pbuf; } ;

/* Variables and functions */
 int HDSPE_MAX_SLOTS ; 
 scalar_t__ HDSPE_PAGE_ADDR_BUF_IN ; 
 scalar_t__ HDSPE_PAGE_ADDR_BUF_OUT ; 
 int /*<<< orphan*/  hdspe_write_4 (struct sc_info*,scalar_t__,scalar_t__) ; 
 scalar_t__ vtophys (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
hdspe_map_dmabuf(struct sc_info *sc)
{
	uint32_t paddr, raddr;
	int i;

	paddr = vtophys(sc->pbuf);
	raddr = vtophys(sc->rbuf);

	for (i = 0; i < HDSPE_MAX_SLOTS * 16; i++) {
		hdspe_write_4(sc, HDSPE_PAGE_ADDR_BUF_OUT + 4 * i,
                    paddr + i * 4096);
		hdspe_write_4(sc, HDSPE_PAGE_ADDR_BUF_IN + 4 * i,
                    raddr + i * 4096);
	}
}