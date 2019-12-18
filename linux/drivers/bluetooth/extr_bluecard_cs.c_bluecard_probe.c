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
struct pcmcia_device {int /*<<< orphan*/  config_flags; struct bluecard_info* priv; int /*<<< orphan*/  dev; } ;
struct bluecard_info {struct pcmcia_device* p_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONF_ENABLE_IRQ ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int bluecard_config (struct pcmcia_device*) ; 
 struct bluecard_info* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bluecard_probe(struct pcmcia_device *link)
{
	struct bluecard_info *info;

	/* Create new info device */
	info = devm_kzalloc(&link->dev, sizeof(*info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	info->p_dev = link;
	link->priv = info;

	link->config_flags |= CONF_ENABLE_IRQ;

	return bluecard_config(link);
}