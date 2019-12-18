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
struct stratix10_rsu_priv {int /*<<< orphan*/  chan; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 struct stratix10_rsu_priv* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  stratix10_svc_free_channel (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stratix10_rsu_remove(struct platform_device *pdev)
{
	struct stratix10_rsu_priv *priv = platform_get_drvdata(pdev);

	stratix10_svc_free_channel(priv->chan);
	return 0;
}