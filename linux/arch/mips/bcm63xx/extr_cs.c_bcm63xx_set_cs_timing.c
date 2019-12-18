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
typedef  unsigned int u32 ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int MPI_CSCTL_HOLD_MASK ; 
 unsigned int MPI_CSCTL_HOLD_SHIFT ; 
 int /*<<< orphan*/  MPI_CSCTL_REG (unsigned int) ; 
 unsigned int MPI_CSCTL_SETUP_MASK ; 
 unsigned int MPI_CSCTL_SETUP_SHIFT ; 
 unsigned int MPI_CSCTL_WAIT_MASK ; 
 unsigned int MPI_CSCTL_WAIT_SHIFT ; 
 int /*<<< orphan*/  bcm63xx_cs_lock ; 
 unsigned int bcm_mpi_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm_mpi_writel (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_valid_cs (unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int bcm63xx_set_cs_timing(unsigned int cs, unsigned int wait,
			   unsigned int setup, unsigned int hold)
{
	unsigned long flags;
	u32 val;

	if (!is_valid_cs(cs))
		return -EINVAL;

	spin_lock_irqsave(&bcm63xx_cs_lock, flags);
	val = bcm_mpi_readl(MPI_CSCTL_REG(cs));
	val &= ~(MPI_CSCTL_WAIT_MASK);
	val &= ~(MPI_CSCTL_SETUP_MASK);
	val &= ~(MPI_CSCTL_HOLD_MASK);
	val |= wait << MPI_CSCTL_WAIT_SHIFT;
	val |= setup << MPI_CSCTL_SETUP_SHIFT;
	val |= hold << MPI_CSCTL_HOLD_SHIFT;
	bcm_mpi_writel(val, MPI_CSCTL_REG(cs));
	spin_unlock_irqrestore(&bcm63xx_cs_lock, flags);

	return 0;
}