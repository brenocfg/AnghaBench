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
typedef  int /*<<< orphan*/  u32 ;
struct i2c_device_id {int dummy; } ;
struct TYPE_2__ {struct device_node* of_node; } ;
struct i2c_client {TYPE_1__ dev; int /*<<< orphan*/  irq; } ;
struct device_node {int dummy; } ;
struct adnp {struct i2c_client* client; int /*<<< orphan*/  i2c_lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int adnp_gpio_setup (struct adnp*,int /*<<< orphan*/ ) ; 
 int adnp_irq_setup (struct adnp*) ; 
 struct adnp* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct adnp*) ; 
 int /*<<< orphan*/  irq_of_parse_and_map (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ of_find_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int adnp_i2c_probe(struct i2c_client *client,
				    const struct i2c_device_id *id)
{
	struct device_node *np = client->dev.of_node;
	struct adnp *adnp;
	u32 num_gpios;
	int err;

	err = of_property_read_u32(np, "nr-gpios", &num_gpios);
	if (err < 0)
		return err;

	client->irq = irq_of_parse_and_map(np, 0);
	if (!client->irq)
		return -EPROBE_DEFER;

	adnp = devm_kzalloc(&client->dev, sizeof(*adnp), GFP_KERNEL);
	if (!adnp)
		return -ENOMEM;

	mutex_init(&adnp->i2c_lock);
	adnp->client = client;

	err = adnp_gpio_setup(adnp, num_gpios);
	if (err)
		return err;

	if (of_find_property(np, "interrupt-controller", NULL)) {
		err = adnp_irq_setup(adnp);
		if (err)
			return err;
	}

	i2c_set_clientdata(client, adnp);

	return 0;
}