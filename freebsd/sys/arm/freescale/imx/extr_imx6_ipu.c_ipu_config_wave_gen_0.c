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
typedef  int uint32_t ;
struct ipu_softc {int dummy; } ;

/* Variables and functions */
 int DI_OFFSET_VALUE (int) ; 
 int DI_RUN_RESOLUTION (int) ; 
 int DI_RUN_VALUE_M1 (int) ; 
 int IPU_DI0_SW_GEN0_1 ; 
 int IPU_DI1_SW_GEN0_1 ; 
 int /*<<< orphan*/  IPU_WRITE4 (struct ipu_softc*,int,int) ; 

__attribute__((used)) static void
ipu_config_wave_gen_0(struct ipu_softc *sc, int di,
	int wave_gen, int run_value, int run_res,
	int offset_value, int offset_res)
{
	uint32_t addr, reg;

	addr = (di ? IPU_DI1_SW_GEN0_1 : IPU_DI0_SW_GEN0_1)
	    + (wave_gen - 1) * sizeof(uint32_t);
	reg = DI_RUN_VALUE_M1(run_value) |
	    DI_RUN_RESOLUTION(run_res) |
	    DI_OFFSET_VALUE(offset_value) | offset_res;
	IPU_WRITE4(sc, addr, reg);
}