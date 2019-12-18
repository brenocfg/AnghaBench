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
struct i2c_adapter {int dummy; } ;
struct pmac_i2c_bus {struct i2c_adapter adapter; } ;

/* Variables and functions */

struct i2c_adapter *pmac_i2c_get_adapter(struct pmac_i2c_bus *bus)
{
	return &bus->adapter;
}