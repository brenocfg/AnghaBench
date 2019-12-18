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
struct pcmcia_device {int config_flags; struct dtl1_info* priv; int /*<<< orphan*/  dev; } ;
struct dtl1_info {struct pcmcia_device* p_dev; } ;

/* Variables and functions */
 int CONF_AUTO_SET_IO ; 
 int CONF_ENABLE_IRQ ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct dtl1_info* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int dtl1_config (struct pcmcia_device*) ; 

__attribute__((used)) static int dtl1_probe(struct pcmcia_device *link)
{
	struct dtl1_info *info;

	/* Create new info device */
	info = devm_kzalloc(&link->dev, sizeof(*info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	info->p_dev = link;
	link->priv = info;

	link->config_flags |= CONF_ENABLE_IRQ | CONF_AUTO_SET_IO;

	return dtl1_config(link);
}