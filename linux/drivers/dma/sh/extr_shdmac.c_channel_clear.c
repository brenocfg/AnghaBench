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
typedef  int u32 ;
struct sh_dmae_device {scalar_t__ chan_reg; TYPE_2__* pdata; } ;
struct sh_dmae_channel {int chclr_bit; scalar_t__ chclr_offset; } ;
struct TYPE_3__ {int id; } ;
struct sh_dmae_chan {TYPE_1__ shdma_chan; } ;
struct TYPE_4__ {scalar_t__ chclr_bitwise; struct sh_dmae_channel* channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  __raw_writel (int,scalar_t__) ; 
 struct sh_dmae_device* to_sh_dev (struct sh_dmae_chan*) ; 

__attribute__((used)) static void channel_clear(struct sh_dmae_chan *sh_dc)
{
	struct sh_dmae_device *shdev = to_sh_dev(sh_dc);
	const struct sh_dmae_channel *chan_pdata = shdev->pdata->channel +
		sh_dc->shdma_chan.id;
	u32 val = shdev->pdata->chclr_bitwise ? 1 << chan_pdata->chclr_bit : 0;

	__raw_writel(val, shdev->chan_reg + chan_pdata->chclr_offset);
}