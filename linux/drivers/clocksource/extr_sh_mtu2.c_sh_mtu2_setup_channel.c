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
struct sh_mtu2_device {TYPE_1__* pdev; scalar_t__ mapbase; } ;
struct sh_mtu2_channel {unsigned int index; scalar_t__ base; struct sh_mtu2_device* mtu; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int IRQF_IRQPOLL ; 
 int IRQF_NOBALANCING ; 
 int IRQF_TIMER ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned int,int) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int platform_get_irq_byname (TYPE_1__*,char*) ; 
 int request_irq (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct sh_mtu2_channel*) ; 
 scalar_t__* sh_mtu2_channel_offsets ; 
 int /*<<< orphan*/  sh_mtu2_interrupt ; 
 int sh_mtu2_register (struct sh_mtu2_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 

__attribute__((used)) static int sh_mtu2_setup_channel(struct sh_mtu2_channel *ch, unsigned int index,
				 struct sh_mtu2_device *mtu)
{
	char name[6];
	int irq;
	int ret;

	ch->mtu = mtu;

	sprintf(name, "tgi%ua", index);
	irq = platform_get_irq_byname(mtu->pdev, name);
	if (irq < 0) {
		/* Skip channels with no declared interrupt. */
		return 0;
	}

	ret = request_irq(irq, sh_mtu2_interrupt,
			  IRQF_TIMER | IRQF_IRQPOLL | IRQF_NOBALANCING,
			  dev_name(&ch->mtu->pdev->dev), ch);
	if (ret) {
		dev_err(&ch->mtu->pdev->dev, "ch%u: failed to request irq %d\n",
			index, irq);
		return ret;
	}

	ch->base = mtu->mapbase + sh_mtu2_channel_offsets[index];
	ch->index = index;

	return sh_mtu2_register(ch, dev_name(&mtu->pdev->dev));
}