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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct imx_dsp_ipc {struct imx_dsp_chan* chans; } ;
struct imx_dsp_chan {int /*<<< orphan*/  ch; } ;

/* Variables and functions */
 int DSP_MU_CHAN_NUM ; 
 struct imx_dsp_ipc* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbox_free_channel (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int imx_dsp_remove(struct platform_device *pdev)
{
	struct imx_dsp_chan *dsp_chan;
	struct imx_dsp_ipc *dsp_ipc;
	int i;

	dsp_ipc = dev_get_drvdata(&pdev->dev);

	for (i = 0; i < DSP_MU_CHAN_NUM; i++) {
		dsp_chan = &dsp_ipc->chans[i];
		mbox_free_channel(dsp_chan->ch);
	}

	return 0;
}