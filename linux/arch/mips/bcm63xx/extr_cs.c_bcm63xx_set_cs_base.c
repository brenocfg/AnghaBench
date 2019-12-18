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

/* Variables and functions */
 int EINVAL ; 
 int MPI_CSBASE_BASE_MASK ; 
 int /*<<< orphan*/  MPI_CSBASE_REG (unsigned int) ; 
 int MPI_CSBASE_SIZE_SHIFT ; 
 int /*<<< orphan*/  bcm63xx_cs_lock ; 
 int /*<<< orphan*/  bcm_mpi_writel (int,int /*<<< orphan*/ ) ; 
 int ilog2 (int) ; 
 int /*<<< orphan*/  is_valid_cs (unsigned int) ; 
 unsigned int roundup_pow_of_two (unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int bcm63xx_set_cs_base(unsigned int cs, u32 base, unsigned int size)
{
	unsigned long flags;
	u32 val;

	if (!is_valid_cs(cs))
		return -EINVAL;

	/* sanity check on size */
	if (size != roundup_pow_of_two(size))
		return -EINVAL;

	if (size < 8 * 1024 || size > 256 * 1024 * 1024)
		return -EINVAL;

	val = (base & MPI_CSBASE_BASE_MASK);
	/* 8k => 0 - 256M => 15 */
	val |= (ilog2(size) - ilog2(8 * 1024)) << MPI_CSBASE_SIZE_SHIFT;

	spin_lock_irqsave(&bcm63xx_cs_lock, flags);
	bcm_mpi_writel(val, MPI_CSBASE_REG(cs));
	spin_unlock_irqrestore(&bcm63xx_cs_lock, flags);

	return 0;
}