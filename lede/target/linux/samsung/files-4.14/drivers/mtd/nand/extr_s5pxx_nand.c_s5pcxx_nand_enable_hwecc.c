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
struct s5p_nand_host {scalar_t__ ecc_base; scalar_t__ nf_base; } ;
struct TYPE_2__ {int size; } ;
struct nand_chip {TYPE_1__ ecc; struct s5p_nand_host* priv; } ;
struct mtd_info {struct nand_chip* priv; } ;

/* Variables and functions */
 int NAND_ECC_WRITE ; 
 scalar_t__ S5P_NFCONT ; 
 int S5P_NFCONT_MECCLOCK ; 
 scalar_t__ S5P_NFECCCONF ; 
 scalar_t__ S5P_NFECCCONT ; 
 int S5P_NFECCCONT_ECCDIRWR ; 
 int S5P_NFECCCONT_MECCINIT ; 
 scalar_t__ S5P_NFECCSTAT ; 
 int /*<<< orphan*/  rwl (scalar_t__,int,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void s5pcxx_nand_enable_hwecc(struct mtd_info *mtd, int mode)
{
	struct nand_chip *chip = mtd->priv;
	struct s5p_nand_host *host = chip->priv;

	uint32_t reg;

	/* Set ECC mode */
	reg = 3; /* 8-bit */
	reg |= (chip->ecc.size - 1) << 16;
	writel(reg, host->ecc_base + S5P_NFECCCONF);

	/* Set ECC direction */
	rwl(host->ecc_base + S5P_NFECCCONT, S5P_NFECCCONT_ECCDIRWR,
	    (mode == NAND_ECC_WRITE) ? S5P_NFECCCONT_ECCDIRWR : 0);

	/* Reset status bits */
	rwl(host->ecc_base + S5P_NFECCSTAT, 0, (1 << 24) | (1 << 25));

	/* Unlock ECC */
	rwl(host->nf_base + S5P_NFCONT, S5P_NFCONT_MECCLOCK, 0);

	/* Initialize ECC */
	rwl(host->ecc_base +S5P_NFECCCONT, 0, S5P_NFECCCONT_MECCINIT);
}