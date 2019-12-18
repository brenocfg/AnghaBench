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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct rio_priv {scalar_t__ maint_win; TYPE_1__* maint_atmu_regs; } ;
struct rio_mport {struct rio_priv* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  rowtear; int /*<<< orphan*/  rowtar; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IS_ALIGNED (int,int) ; 
 int RIO_MAINT_WIN_SIZE ; 
 int /*<<< orphan*/  __fsl_read_rio_config (int,int*,int,char*) ; 
 int /*<<< orphan*/  fsl_rio_config_lock ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int,int,int,...) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
fsl_rio_config_read(struct rio_mport *mport, int index, u16 destid,
			u8 hopcount, u32 offset, int len, u32 *val)
{
	struct rio_priv *priv = mport->priv;
	unsigned long flags;
	u8 *data;
	u32 rval, err = 0;

	pr_debug
		("fsl_rio_config_read:"
		" index %d destid %d hopcount %d offset %8.8x len %d\n",
		index, destid, hopcount, offset, len);

	/* 16MB maintenance window possible */
	/* allow only aligned access to maintenance registers */
	if (offset > (0x1000000 - len) || !IS_ALIGNED(offset, len))
		return -EINVAL;

	spin_lock_irqsave(&fsl_rio_config_lock, flags);

	out_be32(&priv->maint_atmu_regs->rowtar,
		 (destid << 22) | (hopcount << 12) | (offset >> 12));
	out_be32(&priv->maint_atmu_regs->rowtear, (destid >> 10));

	data = (u8 *) priv->maint_win + (offset & (RIO_MAINT_WIN_SIZE - 1));
	switch (len) {
	case 1:
		__fsl_read_rio_config(rval, data, err, "lbz");
		break;
	case 2:
		__fsl_read_rio_config(rval, data, err, "lhz");
		break;
	case 4:
		__fsl_read_rio_config(rval, data, err, "lwz");
		break;
	default:
		spin_unlock_irqrestore(&fsl_rio_config_lock, flags);
		return -EINVAL;
	}

	if (err) {
		pr_debug("RIO: cfg_read error %d for %x:%x:%x\n",
			 err, destid, hopcount, offset);
	}

	spin_unlock_irqrestore(&fsl_rio_config_lock, flags);
	*val = rval;

	return err;
}