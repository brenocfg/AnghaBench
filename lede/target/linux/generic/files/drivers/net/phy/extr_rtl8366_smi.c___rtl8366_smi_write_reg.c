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
struct rtl8366_smi {int cmd_write; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtl8366_smi_start (struct rtl8366_smi*) ; 
 int /*<<< orphan*/  rtl8366_smi_stop (struct rtl8366_smi*) ; 
 int rtl8366_smi_write_byte (struct rtl8366_smi*,int) ; 
 int rtl8366_smi_write_byte_noack (struct rtl8366_smi*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int __rtl8366_smi_write_reg(struct rtl8366_smi *smi,
				   u32 addr, u32 data, bool ack)
{
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&smi->lock, flags);

	rtl8366_smi_start(smi);

	/* send WRITE command */
	ret = rtl8366_smi_write_byte(smi, smi->cmd_write);
	if (ret)
		goto out;

	/* set ADDR[7:0] */
	ret = rtl8366_smi_write_byte(smi, addr & 0xff);
	if (ret)
		goto out;

	/* set ADDR[15:8] */
	ret = rtl8366_smi_write_byte(smi, addr >> 8);
	if (ret)
		goto out;

	/* write DATA[7:0] */
	ret = rtl8366_smi_write_byte(smi, data & 0xff);
	if (ret)
		goto out;

	/* write DATA[15:8] */
	if (ack)
		ret = rtl8366_smi_write_byte(smi, data >> 8);
	else
		ret = rtl8366_smi_write_byte_noack(smi, data >> 8);
	if (ret)
		goto out;

	ret = 0;

 out:
	rtl8366_smi_stop(smi);
	spin_unlock_irqrestore(&smi->lock, flags);

	return ret;
}