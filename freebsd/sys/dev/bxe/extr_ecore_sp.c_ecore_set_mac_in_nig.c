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
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_IS_MF_SI_MODE (struct bxe_softc*) ; 
 int ECORE_LLH_CAM_MAX_PF_LINE ; 
 int /*<<< orphan*/  ECORE_MSG (struct bxe_softc*,char*,char*,int) ; 
 scalar_t__ ECORE_PORT_ID (struct bxe_softc*) ; 
 int /*<<< orphan*/  ECORE_REG_WR_DMAE_LEN (struct bxe_softc*,int,int*,int) ; 
 int /*<<< orphan*/  IS_MF_AFEX (struct bxe_softc*) ; 
 int NIG_REG_LLH0_FUNC_MEM ; 
 scalar_t__ NIG_REG_LLH0_FUNC_MEM_ENABLE ; 
 int NIG_REG_LLH1_FUNC_MEM ; 
 scalar_t__ NIG_REG_LLH1_FUNC_MEM_ENABLE ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,scalar_t__,int) ; 

void ecore_set_mac_in_nig(struct bxe_softc *sc,
			  bool add, unsigned char *dev_addr, int index)
{
	uint32_t wb_data[2];
	uint32_t reg_offset = ECORE_PORT_ID(sc) ? NIG_REG_LLH1_FUNC_MEM :
			 NIG_REG_LLH0_FUNC_MEM;

	if (!ECORE_IS_MF_SI_MODE(sc) && !IS_MF_AFEX(sc))
		return;

	if (index > ECORE_LLH_CAM_MAX_PF_LINE)
		return;

	ECORE_MSG(sc, "Going to %s LLH configuration at entry %d\n",
		  (add ? "ADD" : "DELETE"), index);

	if (add) {
		/* LLH_FUNC_MEM is a uint64_t WB register */
		reg_offset += 8*index;

		wb_data[0] = ((dev_addr[2] << 24) | (dev_addr[3] << 16) |
			      (dev_addr[4] <<  8) |  dev_addr[5]);
		wb_data[1] = ((dev_addr[0] <<  8) |  dev_addr[1]);

		ECORE_REG_WR_DMAE_LEN(sc, reg_offset, wb_data, 2);
	}

	REG_WR(sc, (ECORE_PORT_ID(sc) ? NIG_REG_LLH1_FUNC_MEM_ENABLE :
				  NIG_REG_LLH0_FUNC_MEM_ENABLE) + 4*index, add);
}