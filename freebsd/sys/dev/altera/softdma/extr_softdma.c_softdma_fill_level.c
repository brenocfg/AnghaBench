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
typedef  int /*<<< orphan*/  uint32_t ;
struct softdma_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_ONCHIP_FIFO_MEM_CORE_STATUS_REG_FILL_LEVEL ; 
 int /*<<< orphan*/  softdma_memc_read (struct softdma_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
softdma_fill_level(struct softdma_softc *sc)
{
	uint32_t val;

	val = softdma_memc_read(sc,
	    A_ONCHIP_FIFO_MEM_CORE_STATUS_REG_FILL_LEVEL);

	return (val);
}