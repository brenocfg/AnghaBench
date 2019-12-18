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
struct xenbus_device_id {int dummy; } ;
struct xenbus_device {int /*<<< orphan*/  dev; } ;
struct tpm_private {int /*<<< orphan*/  chip; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct tpm_private*) ; 
 struct tpm_private* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ring_free (struct tpm_private*) ; 
 int setup_chip (int /*<<< orphan*/ *,struct tpm_private*) ; 
 int setup_ring (struct xenbus_device*,struct tpm_private*) ; 
 int tpm_chip_register (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tpm_get_timeouts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xenbus_dev_fatal (struct xenbus_device*,int,char*) ; 

__attribute__((used)) static int tpmfront_probe(struct xenbus_device *dev,
		const struct xenbus_device_id *id)
{
	struct tpm_private *priv;
	int rv;

	priv = kzalloc(sizeof(*priv), GFP_KERNEL);
	if (!priv) {
		xenbus_dev_fatal(dev, -ENOMEM, "allocating priv structure");
		return -ENOMEM;
	}

	rv = setup_chip(&dev->dev, priv);
	if (rv) {
		kfree(priv);
		return rv;
	}

	rv = setup_ring(dev, priv);
	if (rv) {
		ring_free(priv);
		return rv;
	}

	tpm_get_timeouts(priv->chip);

	return tpm_chip_register(priv->chip);
}