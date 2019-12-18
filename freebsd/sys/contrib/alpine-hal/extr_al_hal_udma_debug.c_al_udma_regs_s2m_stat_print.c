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
 int /*<<< orphan*/  comp_desc ; 
 int /*<<< orphan*/  comp_pkt ; 
 int /*<<< orphan*/  drop_pkt ; 
 int /*<<< orphan*/  prefed_desc ; 
 int /*<<< orphan*/  rx_bytes_high ; 
 int /*<<< orphan*/  rx_bytes_low ; 
 int /*<<< orphan*/  s2m ; 
 int /*<<< orphan*/  s2m_stat ; 

__attribute__((used)) static void al_udma_regs_s2m_stat_print(struct al_udma *udma)
{
	al_dbg("S2M statistics regs:\n");
	AL_UDMA_PRINT_REG(udma, " ", "\n", s2m, s2m_stat, drop_pkt);
	AL_UDMA_PRINT_REG(udma, " ", "\n", s2m, s2m_stat, rx_bytes_low);
	AL_UDMA_PRINT_REG(udma, " ", "\n", s2m, s2m_stat, rx_bytes_high);
	AL_UDMA_PRINT_REG(udma, " ", "\n", s2m, s2m_stat, prefed_desc);
	AL_UDMA_PRINT_REG(udma, " ", "\n", s2m, s2m_stat, comp_pkt);
	AL_UDMA_PRINT_REG(udma, " ", "\n", s2m, s2m_stat, comp_desc);
	AL_UDMA_PRINT_REG(udma, " ", "\n", s2m, s2m_stat, ack_pkts);
}