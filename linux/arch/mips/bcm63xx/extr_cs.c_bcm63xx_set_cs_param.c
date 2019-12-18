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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MPI_CSCTL_DATA16_MASK ; 
 int /*<<< orphan*/  MPI_CSCTL_ENDIANSWAP_MASK ; 
 int /*<<< orphan*/  MPI_CSCTL_REG (unsigned int) ; 
 int /*<<< orphan*/  MPI_CSCTL_SYNCMODE_MASK ; 
 int /*<<< orphan*/  MPI_CSCTL_TSIZE_MASK ; 
 unsigned int MPI_CS_PCMCIA_ATTR ; 
 unsigned int MPI_CS_PCMCIA_COMMON ; 
 unsigned int MPI_CS_PCMCIA_IO ; 
 int /*<<< orphan*/  bcm63xx_cs_lock ; 
 int /*<<< orphan*/  bcm_mpi_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm_mpi_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_valid_cs (unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int bcm63xx_set_cs_param(unsigned int cs, u32 params)
{
	unsigned long flags;
	u32 val;

	if (!is_valid_cs(cs))
		return -EINVAL;

	/* none of this fields apply to pcmcia */
	if (cs == MPI_CS_PCMCIA_COMMON ||
	    cs == MPI_CS_PCMCIA_ATTR ||
	    cs == MPI_CS_PCMCIA_IO)
		return -EINVAL;

	spin_lock_irqsave(&bcm63xx_cs_lock, flags);
	val = bcm_mpi_readl(MPI_CSCTL_REG(cs));
	val &= ~(MPI_CSCTL_DATA16_MASK);
	val &= ~(MPI_CSCTL_SYNCMODE_MASK);
	val &= ~(MPI_CSCTL_TSIZE_MASK);
	val &= ~(MPI_CSCTL_ENDIANSWAP_MASK);
	val |= params;
	bcm_mpi_writel(val, MPI_CSCTL_REG(cs));
	spin_unlock_irqrestore(&bcm63xx_cs_lock, flags);

	return 0;
}