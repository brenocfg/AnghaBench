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
 int /*<<< orphan*/  ack_pkts ; 
 int /*<<< orphan*/  al_dbg (char*) ; 
 int /*<<< orphan*/  cfg_st ; 
 int /*<<< orphan*/  comp_desc ; 
 int /*<<< orphan*/  comp_pkt ; 
 int /*<<< orphan*/  m2s ; 
 int /*<<< orphan*/  m2s_stat ; 
 int /*<<< orphan*/  prefed_desc ; 
 int /*<<< orphan*/  tx_bytes_high ; 
 int /*<<< orphan*/  tx_bytes_low ; 
 int /*<<< orphan*/  tx_pkt ; 

__attribute__((used)) static void al_udma_regs_m2s_stat_print(struct al_udma *udma)
{
	al_dbg("M2S statistics regs:\n");
	AL_UDMA_PRINT_REG(udma, " ", "\n", m2s, m2s_stat, cfg_st);
	AL_UDMA_PRINT_REG(udma, " ", "\n", m2s, m2s_stat, tx_pkt);
	AL_UDMA_PRINT_REG(udma, " ", "\n", m2s, m2s_stat, tx_bytes_low);
	AL_UDMA_PRINT_REG(udma, " ", "\n", m2s, m2s_stat, tx_bytes_high);
	AL_UDMA_PRINT_REG(udma, " ", "\n", m2s, m2s_stat, prefed_desc);
	AL_UDMA_PRINT_REG(udma, " ", "\n", m2s, m2s_stat, comp_pkt);
	AL_UDMA_PRINT_REG(udma, " ", "\n", m2s, m2s_stat, comp_desc);
	AL_UDMA_PRINT_REG(udma, " ", "\n", m2s, m2s_stat, ack_pkts);
}