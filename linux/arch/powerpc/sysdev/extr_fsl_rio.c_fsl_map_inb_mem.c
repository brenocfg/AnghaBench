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
typedef  int u64 ;
typedef  int u32 ;
struct rio_priv {TYPE_1__* inb_atmu_regs; } ;
struct rio_mport {struct rio_priv* priv; } ;
typedef  int dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  riwar; int /*<<< orphan*/  riwbar; int /*<<< orphan*/  riwtar; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int RIO_INB_ATMU_COUNT ; 
 int RIWAR_ENABLE ; 
 int RIWAR_RDTYP_SNOOP ; 
 int RIWAR_SIZE_MASK ; 
 int RIWAR_TGINT_LOCAL ; 
 int RIWAR_WRTYP_SNOOP ; 
 int RIWBAR_BADD_MASK ; 
 int RIWBAR_BADD_VAL_SHIFT ; 
 int RIWTAR_TRAD_VAL_SHIFT ; 
 unsigned int ilog2 (int) ; 
 int in_be32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ *,int) ; 

int fsl_map_inb_mem(struct rio_mport *mport, dma_addr_t lstart,
	u64 rstart, u64 size, u32 flags)
{
	struct rio_priv *priv = mport->priv;
	u32 base_size;
	unsigned int base_size_log;
	u64 win_start, win_end;
	u32 riwar;
	int i;

	if ((size & (size - 1)) != 0 || size > 0x400000000ULL)
		return -EINVAL;

	base_size_log = ilog2(size);
	base_size = 1 << base_size_log;

	/* check if addresses are aligned with the window size */
	if (lstart & (base_size - 1))
		return -EINVAL;
	if (rstart & (base_size - 1))
		return -EINVAL;

	/* check for conflicting ranges */
	for (i = 0; i < RIO_INB_ATMU_COUNT; i++) {
		riwar = in_be32(&priv->inb_atmu_regs[i].riwar);
		if ((riwar & RIWAR_ENABLE) == 0)
			continue;
		win_start = ((u64)(in_be32(&priv->inb_atmu_regs[i].riwbar) & RIWBAR_BADD_MASK))
			<< RIWBAR_BADD_VAL_SHIFT;
		win_end = win_start + ((1 << ((riwar & RIWAR_SIZE_MASK) + 1)) - 1);
		if (rstart < win_end && (rstart + size) > win_start)
			return -EINVAL;
	}

	/* find unused atmu */
	for (i = 0; i < RIO_INB_ATMU_COUNT; i++) {
		riwar = in_be32(&priv->inb_atmu_regs[i].riwar);
		if ((riwar & RIWAR_ENABLE) == 0)
			break;
	}
	if (i >= RIO_INB_ATMU_COUNT)
		return -ENOMEM;

	out_be32(&priv->inb_atmu_regs[i].riwtar, lstart >> RIWTAR_TRAD_VAL_SHIFT);
	out_be32(&priv->inb_atmu_regs[i].riwbar, rstart >> RIWBAR_BADD_VAL_SHIFT);
	out_be32(&priv->inb_atmu_regs[i].riwar, RIWAR_ENABLE | RIWAR_TGINT_LOCAL |
		RIWAR_RDTYP_SNOOP | RIWAR_WRTYP_SNOOP | (base_size_log - 1));

	return 0;
}