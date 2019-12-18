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
struct pcmcia_device {TYPE_1__** resource; struct dtl1_info* priv; } ;
struct dtl1_info {int dummy; } ;
struct TYPE_2__ {int end; } ;

/* Variables and functions */
 int /*<<< orphan*/  dtl1_confcheck ; 
 int /*<<< orphan*/  dtl1_detach (struct pcmcia_device*) ; 
 int /*<<< orphan*/  dtl1_interrupt ; 
 int dtl1_open (struct dtl1_info*) ; 
 int pcmcia_enable_device (struct pcmcia_device*) ; 
 int pcmcia_loop_config (struct pcmcia_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int pcmcia_request_irq (struct pcmcia_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dtl1_config(struct pcmcia_device *link)
{
	struct dtl1_info *info = link->priv;
	int ret;

	/* Look for a generic full-sized window */
	link->resource[0]->end = 8;
	ret = pcmcia_loop_config(link, dtl1_confcheck, NULL);
	if (ret)
		goto failed;

	ret = pcmcia_request_irq(link, dtl1_interrupt);
	if (ret)
		goto failed;

	ret = pcmcia_enable_device(link);
	if (ret)
		goto failed;

	ret = dtl1_open(info);
	if (ret)
		goto failed;

	return 0;

failed:
	dtl1_detach(link);
	return ret;
}