#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  of_node; } ;
struct spi_device {TYPE_2__ dev; } ;
struct TYPE_5__ {scalar_t__ exists; } ;
struct moxtet {int dev_irq; TYPE_2__* dev; TYPE_1__ irq; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_2__*,char*,int) ; 
 struct moxtet* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int moxtet_find_topology (struct moxtet*) ; 
 int moxtet_irq_setup (struct moxtet*) ; 
 int moxtet_register_debugfs (struct moxtet*) ; 
 int /*<<< orphan*/  moxtet_register_devices_from_topology (struct moxtet*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int of_irq_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_register_moxtet_devices (struct moxtet*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct moxtet*) ; 
 int spi_setup (struct spi_device*) ; 

__attribute__((used)) static int moxtet_probe(struct spi_device *spi)
{
	struct moxtet *moxtet;
	int ret;

	ret = spi_setup(spi);
	if (ret < 0)
		return ret;

	moxtet = devm_kzalloc(&spi->dev, sizeof(struct moxtet),
			      GFP_KERNEL);
	if (!moxtet)
		return -ENOMEM;

	moxtet->dev = &spi->dev;
	spi_set_drvdata(spi, moxtet);

	mutex_init(&moxtet->lock);

	moxtet->dev_irq = of_irq_get(moxtet->dev->of_node, 0);
	if (moxtet->dev_irq == -EPROBE_DEFER)
		return -EPROBE_DEFER;

	if (moxtet->dev_irq <= 0) {
		dev_err(moxtet->dev, "No IRQ resource found\n");
		return -ENXIO;
	}

	ret = moxtet_find_topology(moxtet);
	if (ret < 0)
		return ret;

	if (moxtet->irq.exists) {
		ret = moxtet_irq_setup(moxtet);
		if (ret < 0)
			return ret;
	}

	of_register_moxtet_devices(moxtet);
	moxtet_register_devices_from_topology(moxtet);

	ret = moxtet_register_debugfs(moxtet);
	if (ret < 0)
		dev_warn(moxtet->dev, "Failed creating debugfs entries: %i\n",
			 ret);

	return 0;
}