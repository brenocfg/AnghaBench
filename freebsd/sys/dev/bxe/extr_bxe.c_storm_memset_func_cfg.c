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
struct tstorm_eth_function_common_config {int dummy; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 scalar_t__ BAR_TSTRORM_INTMEM ; 
 scalar_t__ TSTORM_FUNCTION_COMMON_CONFIG_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_storm_memset_struct (struct bxe_softc*,scalar_t__,size_t,scalar_t__*) ; 

__attribute__((used)) static void
storm_memset_func_cfg(struct bxe_softc                         *sc,
                      struct tstorm_eth_function_common_config *tcfg,
                      uint16_t                                  abs_fid)
{
    uint32_t addr;
    size_t size;

    addr = (BAR_TSTRORM_INTMEM +
            TSTORM_FUNCTION_COMMON_CONFIG_OFFSET(abs_fid));
    size = sizeof(struct tstorm_eth_function_common_config);
    ecore_storm_memset_struct(sc, addr, size, (uint32_t *)tcfg);
}