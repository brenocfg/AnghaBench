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
typedef  int /*<<< orphan*/  uint16_t ;
struct bxe_softc {int dummy; } ;
typedef  int /*<<< orphan*/  bus_addr_t ;

/* Variables and functions */
 scalar_t__ XSEM_REG_FAST_MEMORY ; 
 scalar_t__ XSTORM_SPQ_PAGE_BASE_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __storm_memset_dma_mapping (struct bxe_softc*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
storm_memset_spq_addr(struct bxe_softc *sc,
                      bus_addr_t       mapping,
                      uint16_t         abs_fid)
{
    uint32_t addr = (XSEM_REG_FAST_MEMORY +
                     XSTORM_SPQ_PAGE_BASE_OFFSET(abs_fid));
    __storm_memset_dma_mapping(sc, addr, mapping);
}