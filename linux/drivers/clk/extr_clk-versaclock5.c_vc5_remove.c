#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vc5_driver_data {int /*<<< orphan*/  pin_xin; TYPE_2__* chip_info; } ;
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;
struct i2c_client {TYPE_1__ dev; } ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int VC5_HAS_INTERNAL_XTAL ; 
 int /*<<< orphan*/  clk_unregister_fixed_rate (int /*<<< orphan*/ ) ; 
 struct vc5_driver_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  of_clk_del_provider (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vc5_remove(struct i2c_client *client)
{
	struct vc5_driver_data *vc5 = i2c_get_clientdata(client);

	of_clk_del_provider(client->dev.of_node);

	if (vc5->chip_info->flags & VC5_HAS_INTERNAL_XTAL)
		clk_unregister_fixed_rate(vc5->pin_xin);

	return 0;
}