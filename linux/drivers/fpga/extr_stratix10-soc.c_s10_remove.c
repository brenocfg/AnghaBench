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
struct s10_priv {int /*<<< orphan*/  chan; } ;
struct platform_device {int dummy; } ;
struct fpga_manager {struct s10_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  fpga_mgr_unregister (struct fpga_manager*) ; 
 struct fpga_manager* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  stratix10_svc_free_channel (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s10_remove(struct platform_device *pdev)
{
	struct fpga_manager *mgr = platform_get_drvdata(pdev);
	struct s10_priv *priv = mgr->priv;

	fpga_mgr_unregister(mgr);
	stratix10_svc_free_channel(priv->chan);

	return 0;
}