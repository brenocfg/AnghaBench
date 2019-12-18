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
struct of_phandle_args {int /*<<< orphan*/  np; } ;
struct mbox_client {int /*<<< orphan*/  rx_callback; struct device* dev; } ;
struct mbox_chan {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IMX_SC_R_MU_0A ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct mbox_chan*) ; 
 int PTR_ERR (struct mbox_chan*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  devm_kfree (struct device*,struct mbox_client*) ; 
 struct mbox_client* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_sc_irq_ipc_handle ; 
 int /*<<< orphan*/  imx_sc_irq_work ; 
 int imx_scu_get_handle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  imx_scu_irq_callback ; 
 int /*<<< orphan*/  imx_scu_irq_work_handler ; 
 struct mbox_chan* mbox_request_channel_byname (struct mbox_client*,char*) ; 
 scalar_t__ mu_resource_id ; 
 int of_alias_get_id (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  of_parse_phandle_with_args (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,struct of_phandle_args*) ; 

int imx_scu_enable_general_irq_channel(struct device *dev)
{
	struct of_phandle_args spec;
	struct mbox_client *cl;
	struct mbox_chan *ch;
	int ret = 0, i = 0;

	ret = imx_scu_get_handle(&imx_sc_irq_ipc_handle);
	if (ret)
		return ret;

	cl = devm_kzalloc(dev, sizeof(*cl), GFP_KERNEL);
	if (!cl)
		return -ENOMEM;

	cl->dev = dev;
	cl->rx_callback = imx_scu_irq_callback;

	/* SCU general IRQ uses general interrupt channel 3 */
	ch = mbox_request_channel_byname(cl, "gip3");
	if (IS_ERR(ch)) {
		ret = PTR_ERR(ch);
		dev_err(dev, "failed to request mbox chan gip3, ret %d\n", ret);
		devm_kfree(dev, cl);
		return ret;
	}

	INIT_WORK(&imx_sc_irq_work, imx_scu_irq_work_handler);

	if (!of_parse_phandle_with_args(dev->of_node, "mboxes",
				       "#mbox-cells", 0, &spec))
		i = of_alias_get_id(spec.np, "mu");

	/* use mu1 as general mu irq channel if failed */
	if (i < 0)
		i = 1;

	mu_resource_id = IMX_SC_R_MU_0A + i;

	return ret;
}