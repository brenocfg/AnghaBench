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
typedef  int u32 ;
struct cppi41_dd {unsigned int n_chans; scalar_t__ sched_mem; } ;

/* Variables and functions */
 scalar_t__ DMA_SCHED_CTRL ; 
 int DMA_SCHED_CTRL_EN ; 
 scalar_t__ DMA_SCHED_WORD (unsigned int) ; 
 int SCHED_ENTRY0_CHAN (unsigned int) ; 
 int SCHED_ENTRY1_CHAN (unsigned int) ; 
 int SCHED_ENTRY1_IS_RX ; 
 int SCHED_ENTRY2_CHAN (unsigned int) ; 
 int SCHED_ENTRY3_CHAN (unsigned int) ; 
 int SCHED_ENTRY3_IS_RX ; 
 int /*<<< orphan*/  cppi_writel (int,scalar_t__) ; 

__attribute__((used)) static void init_sched(struct cppi41_dd *cdd)
{
	unsigned ch;
	unsigned word;
	u32 reg;

	word = 0;
	cppi_writel(0, cdd->sched_mem + DMA_SCHED_CTRL);
	for (ch = 0; ch < cdd->n_chans; ch += 2) {

		reg = SCHED_ENTRY0_CHAN(ch);
		reg |= SCHED_ENTRY1_CHAN(ch) | SCHED_ENTRY1_IS_RX;

		reg |= SCHED_ENTRY2_CHAN(ch + 1);
		reg |= SCHED_ENTRY3_CHAN(ch + 1) | SCHED_ENTRY3_IS_RX;
		cppi_writel(reg, cdd->sched_mem + DMA_SCHED_WORD(word));
		word++;
	}
	reg = cdd->n_chans * 2 - 1;
	reg |= DMA_SCHED_CTRL_EN;
	cppi_writel(reg, cdd->sched_mem + DMA_SCHED_CTRL);
}