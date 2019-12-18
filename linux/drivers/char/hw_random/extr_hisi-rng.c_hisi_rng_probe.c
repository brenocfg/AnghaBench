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
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  read; int /*<<< orphan*/  cleanup; int /*<<< orphan*/  init; int /*<<< orphan*/  name; } ;
struct hisi_rng {TYPE_1__ rng; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int devm_hwrng_register (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct hisi_rng* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hisi_rng_cleanup ; 
 int /*<<< orphan*/  hisi_rng_init ; 
 int /*<<< orphan*/  hisi_rng_read ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct hisi_rng*) ; 

__attribute__((used)) static int hisi_rng_probe(struct platform_device *pdev)
{
	struct hisi_rng *rng;
	struct resource *res;
	int ret;

	rng = devm_kzalloc(&pdev->dev, sizeof(*rng), GFP_KERNEL);
	if (!rng)
		return -ENOMEM;

	platform_set_drvdata(pdev, rng);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	rng->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(rng->base))
		return PTR_ERR(rng->base);

	rng->rng.name = pdev->name;
	rng->rng.init = hisi_rng_init;
	rng->rng.cleanup = hisi_rng_cleanup;
	rng->rng.read = hisi_rng_read;

	ret = devm_hwrng_register(&pdev->dev, &rng->rng);
	if (ret) {
		dev_err(&pdev->dev, "failed to register hwrng\n");
		return ret;
	}

	return 0;
}