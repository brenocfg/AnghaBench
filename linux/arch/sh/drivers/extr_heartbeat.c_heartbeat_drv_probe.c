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
struct resource {int flags; int /*<<< orphan*/  start; } ;
struct TYPE_2__ {struct heartbeat_data* platform_data; } ;
struct platform_device {int num_resources; TYPE_1__ dev; } ;
struct heartbeat_data {int nr_bits; int* bit_pos; int mask; int regsize; int /*<<< orphan*/  timer; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
#define  IORESOURCE_MEM_16BIT 130 
#define  IORESOURCE_MEM_32BIT 129 
#define  IORESOURCE_MEM_8BIT 128 
 int IORESOURCE_MEM_TYPE_MASK ; 
 int* default_bit_pos ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  heartbeat_timer ; 
 int /*<<< orphan*/  ioremap_nocache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  kfree (struct heartbeat_data*) ; 
 struct heartbeat_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct heartbeat_data*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int heartbeat_drv_probe(struct platform_device *pdev)
{
	struct resource *res;
	struct heartbeat_data *hd;
	int i;

	if (unlikely(pdev->num_resources != 1)) {
		dev_err(&pdev->dev, "invalid number of resources\n");
		return -EINVAL;
	}

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (unlikely(res == NULL)) {
		dev_err(&pdev->dev, "invalid resource\n");
		return -EINVAL;
	}

	if (pdev->dev.platform_data) {
		hd = pdev->dev.platform_data;
	} else {
		hd = kzalloc(sizeof(struct heartbeat_data), GFP_KERNEL);
		if (unlikely(!hd))
			return -ENOMEM;
	}

	hd->base = ioremap_nocache(res->start, resource_size(res));
	if (unlikely(!hd->base)) {
		dev_err(&pdev->dev, "ioremap failed\n");

		if (!pdev->dev.platform_data)
			kfree(hd);

		return -ENXIO;
	}

	if (!hd->nr_bits) {
		hd->bit_pos = default_bit_pos;
		hd->nr_bits = ARRAY_SIZE(default_bit_pos);
	}

	hd->mask = 0;
	for (i = 0; i < hd->nr_bits; i++)
		hd->mask |= (1 << hd->bit_pos[i]);

	if (!hd->regsize) {
		switch (res->flags & IORESOURCE_MEM_TYPE_MASK) {
		case IORESOURCE_MEM_32BIT:
			hd->regsize = 32;
			break;
		case IORESOURCE_MEM_16BIT:
			hd->regsize = 16;
			break;
		case IORESOURCE_MEM_8BIT:
		default:
			hd->regsize = 8;
			break;
		}
	}

	timer_setup(&hd->timer, heartbeat_timer, 0);
	platform_set_drvdata(pdev, hd);

	return mod_timer(&hd->timer, jiffies + 1);
}