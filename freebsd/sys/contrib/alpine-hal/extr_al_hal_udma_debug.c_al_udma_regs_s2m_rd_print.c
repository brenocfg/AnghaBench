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
struct al_udma {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AL_UDMA_PRINT_REG (struct al_udma*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  al_dbg (char*) ; 
 int /*<<< orphan*/  desc_pref_cfg_1 ; 
 int /*<<< orphan*/  desc_pref_cfg_2 ; 
 int /*<<< orphan*/  desc_pref_cfg_3 ; 
 int /*<<< orphan*/  desc_pref_cfg_4 ; 
 int /*<<< orphan*/  s2m ; 
 int /*<<< orphan*/  s2m_rd ; 

__attribute__((used)) static void al_udma_regs_s2m_rd_print(struct al_udma *udma)
{
	al_dbg("S2M read regs:\n");
	AL_UDMA_PRINT_REG(udma, " ", "\n", s2m, s2m_rd, desc_pref_cfg_1);
	AL_UDMA_PRINT_REG(udma, " ", "\n", s2m, s2m_rd, desc_pref_cfg_2);
	AL_UDMA_PRINT_REG(udma, " ", "\n", s2m, s2m_rd, desc_pref_cfg_3);
	AL_UDMA_PRINT_REG(udma, " ", "\n", s2m, s2m_rd, desc_pref_cfg_4);
}