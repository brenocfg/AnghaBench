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
struct s5p_nand_host {scalar_t__ nf_base; } ;

/* Variables and functions */
 scalar_t__ S5P_NFCONT ; 
 int S5P_NFCONT_MODE ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void s5p_nand_inithw(struct s5p_nand_host  *host)
{
	u32 value;

	/* Enable NAND Flash Controller */
	value = readl(host->nf_base + S5P_NFCONT);
	writel(value | S5P_NFCONT_MODE, host->nf_base + S5P_NFCONT);
}