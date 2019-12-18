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
 int DI_CNT_AUTO_RELOAD ; 
 int DI_CNT_CLR_SEL (int) ; 
 int DI_CNT_DOWN (int) ; 
 int DI_CNT_POLARITY_CLR_SEL (int) ; 
 int DI_CNT_POLARITY_GEN_EN (int) ; 
 int DI_CNT_POLARITY_TRIGGER_SEL (int) ; 
 int IPU_DI0_STP_REP ; 
 int IPU_DI0_SW_GEN1_1 ; 
 int IPU_DI1_STP_REP ; 
 int IPU_DI1_SW_GEN1_1 ; 
 int IPU_READ4 (struct ipu_softc*,int) ; 
 int /*<<< orphan*/  IPU_WRITE4 (struct ipu_softc*,int,int) ; 

__attribute__((used)) static void
ipu_config_wave_gen_1(struct ipu_softc *sc, int di, int wave_gen,
	int repeat_count, int cnt_clr_src,
	int cnt_polarity_gen_en,
	int cnt_polarity_clr_src,
	int cnt_polarity_trigger_src,
	int cnt_up, int cnt_down)
{
	uint32_t addr, reg;

	addr = (di ? IPU_DI1_SW_GEN1_1 : IPU_DI0_SW_GEN1_1)
	    + (wave_gen - 1) * sizeof(uint32_t);
	reg = DI_CNT_POLARITY_GEN_EN(cnt_polarity_gen_en) |
	    DI_CNT_CLR_SEL(cnt_clr_src) |
	    DI_CNT_POLARITY_TRIGGER_SEL(cnt_polarity_trigger_src) |
	    DI_CNT_POLARITY_CLR_SEL(cnt_polarity_clr_src);
	reg |= DI_CNT_DOWN(cnt_down) | cnt_up;
	if (repeat_count == 0)
		reg |= DI_CNT_AUTO_RELOAD;
	IPU_WRITE4(sc, addr, reg);

	addr = (di ? IPU_DI1_STP_REP : IPU_DI0_STP_REP)
	    + (wave_gen - 1) / 2 * sizeof(uint32_t);
	reg = IPU_READ4(sc, addr);
	if (wave_gen % 2) {
		reg &= ~(0xffff);
		reg |= repeat_count;
	}
	else {
		reg &= ~(0xffff << 16);
		reg |= (repeat_count << 16);
	}
	IPU_WRITE4(sc, addr, reg);
}