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
struct TYPE_2__ {void const* out; } ;
struct i3c_priv_xfer {int rnw; size_t len; TYPE_1__ data; } ;
struct i3c_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct i3c_device* dev_to_i3cdev (struct device*) ; 
 int i3c_device_do_priv_xfers (struct i3c_device*,struct i3c_priv_xfer*,int) ; 

__attribute__((used)) static int regmap_i3c_write(void *context, const void *data, size_t count)
{
	struct device *dev = context;
	struct i3c_device *i3c = dev_to_i3cdev(dev);
	struct i3c_priv_xfer xfers[] = {
		{
			.rnw = false,
			.len = count,
			.data.out = data,
		},
	};

	return i3c_device_do_priv_xfers(i3c, xfers, 1);
}