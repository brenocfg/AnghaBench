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
struct TYPE_2__ {unsigned long priv; int /*<<< orphan*/  data_read; int /*<<< orphan*/  data_present; int /*<<< orphan*/  init; int /*<<< orphan*/  name; } ;
struct talitos_private {int rng_registered; TYPE_1__ rng; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_driver_string (struct device*) ; 
 struct talitos_private* dev_get_drvdata (struct device*) ; 
 int hwrng_register (TYPE_1__*) ; 
 int /*<<< orphan*/  talitos_rng_data_present ; 
 int /*<<< orphan*/  talitos_rng_data_read ; 
 int /*<<< orphan*/  talitos_rng_init ; 

__attribute__((used)) static int talitos_register_rng(struct device *dev)
{
	struct talitos_private *priv = dev_get_drvdata(dev);
	int err;

	priv->rng.name		= dev_driver_string(dev),
	priv->rng.init		= talitos_rng_init,
	priv->rng.data_present	= talitos_rng_data_present,
	priv->rng.data_read	= talitos_rng_data_read,
	priv->rng.priv		= (unsigned long)dev;

	err = hwrng_register(&priv->rng);
	if (!err)
		priv->rng_registered = true;

	return err;
}