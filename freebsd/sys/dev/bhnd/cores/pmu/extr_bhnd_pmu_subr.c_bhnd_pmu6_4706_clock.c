#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int u_int ;
struct bhnd_pmu_query {int /*<<< orphan*/  io_ctx; TYPE_1__* io; } ;
struct TYPE_2__ {int (* rd_chipst ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int BHND_PMU6_4706_PROCPLL_OFF ; 
 int /*<<< orphan*/  BHND_PMU6_4706_PROC_NDIV_INT ; 
 int /*<<< orphan*/  BHND_PMU6_4706_PROC_P1DIV ; 
 int /*<<< orphan*/  BHND_PMU6_4706_PROC_P2DIV ; 
#define  BHND_PMU6_MAINPLL_CPU 130 
#define  BHND_PMU6_MAINPLL_MEM 129 
#define  BHND_PMU6_MAINPLL_SI 128 
 int BHND_PMU_GET_BITS (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BHND_PMU_PLL_CONTROL_ADDR ; 
 int /*<<< orphan*/  BHND_PMU_PLL_CONTROL_DATA ; 
 int BHND_PMU_READ_4 (struct bhnd_pmu_query*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BHND_PMU_WRITE_4 (struct bhnd_pmu_query*,int /*<<< orphan*/ ,int) ; 
 int CHIPC_CST4706_LOWCOST_PKG ; 
 int /*<<< orphan*/  PMU_LOG (struct bhnd_pmu_query*,char*,int) ; 
 int stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
bhnd_pmu6_4706_clock(struct bhnd_pmu_query *sc, u_int pll0, u_int m)
{
	uint32_t chipst, clock;
	uint32_t ndiv, p1div, p2div, tmp;

	/* Get N, P1 and P2 dividers to determine CPU clock */
	BHND_PMU_WRITE_4(sc, BHND_PMU_PLL_CONTROL_ADDR,
	    pll0 + BHND_PMU6_4706_PROCPLL_OFF);
	BHND_PMU_READ_4(sc, BHND_PMU_PLL_CONTROL_ADDR);

	tmp = BHND_PMU_READ_4(sc, BHND_PMU_PLL_CONTROL_DATA);
	ndiv = BHND_PMU_GET_BITS(tmp, BHND_PMU6_4706_PROC_NDIV_INT);
	p1div = BHND_PMU_GET_BITS(tmp, BHND_PMU6_4706_PROC_P1DIV);
	p2div = BHND_PMU_GET_BITS(tmp, BHND_PMU6_4706_PROC_P2DIV);

	/* Fixed 25MHz reference clock */
	clock = 25 * 1000 * 1000;

	/* The low-cost bonding uses an input divider of 4; otherwise, 2 */
	chipst = sc->io->rd_chipst(sc->io_ctx);
	if (chipst & CHIPC_CST4706_LOWCOST_PKG)
		clock /= 4;
	else
		clock /= 2;

	clock *= ndiv * p2div / p1div;

	switch (m) {
	case BHND_PMU6_MAINPLL_CPU:
		return (clock);
	case BHND_PMU6_MAINPLL_MEM:
		return (clock / 2);
	case BHND_PMU6_MAINPLL_SI:
		return (clock / 4);
	default:
		PMU_LOG(sc, "bad m divider: %d", m);
		return (0);
	}
}