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
struct bwi_softc {int dummy; } ;
struct bwi_ring_data {int dummy; } ;
typedef  int /*<<< orphan*/  bus_addr_t ;

/* Variables and functions */

__attribute__((used)) static void
bwi_setup_tx_desc64(struct bwi_softc *sc, struct bwi_ring_data *rd,
		    int buf_idx, bus_addr_t paddr, int buf_len)
{
	/* TODO:64 */
}