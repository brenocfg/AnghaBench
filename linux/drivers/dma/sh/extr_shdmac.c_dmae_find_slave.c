#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sh_dmae_slave_config {int slave_id; int mid_rid; } ;
struct sh_dmae_pdata {int slave_num; struct sh_dmae_slave_config* slave; } ;
struct sh_dmae_device {struct sh_dmae_pdata* pdata; } ;
struct TYPE_4__ {int slave_id; TYPE_1__* dev; } ;
struct sh_dmae_chan {TYPE_2__ shdma_chan; } ;
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int SH_DMA_SLAVE_NUMBER ; 
 struct sh_dmae_device* to_sh_dev (struct sh_dmae_chan*) ; 

__attribute__((used)) static const struct sh_dmae_slave_config *dmae_find_slave(
	struct sh_dmae_chan *sh_chan, int match)
{
	struct sh_dmae_device *shdev = to_sh_dev(sh_chan);
	const struct sh_dmae_pdata *pdata = shdev->pdata;
	const struct sh_dmae_slave_config *cfg;
	int i;

	if (!sh_chan->shdma_chan.dev->of_node) {
		if (match >= SH_DMA_SLAVE_NUMBER)
			return NULL;

		for (i = 0, cfg = pdata->slave; i < pdata->slave_num; i++, cfg++)
			if (cfg->slave_id == match)
				return cfg;
	} else {
		for (i = 0, cfg = pdata->slave; i < pdata->slave_num; i++, cfg++)
			if (cfg->mid_rid == match) {
				sh_chan->shdma_chan.slave_id = i;
				return cfg;
			}
	}

	return NULL;
}