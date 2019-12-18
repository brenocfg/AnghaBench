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
struct sm5502_muic_info {int /*<<< orphan*/  irq_data; int /*<<< orphan*/  irq; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct sm5502_muic_info* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  regmap_del_irq_chip (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sm5502_muic_i2c_remove(struct i2c_client *i2c)
{
	struct sm5502_muic_info *info = i2c_get_clientdata(i2c);

	regmap_del_irq_chip(info->irq, info->irq_data);

	return 0;
}