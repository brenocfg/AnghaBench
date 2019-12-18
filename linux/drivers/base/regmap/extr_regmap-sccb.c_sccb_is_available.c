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
typedef  int u32 ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int I2C_FUNC_SMBUS_BYTE ; 
 int I2C_FUNC_SMBUS_WRITE_BYTE_DATA ; 
 int i2c_get_functionality (struct i2c_adapter*) ; 

__attribute__((used)) static bool sccb_is_available(struct i2c_adapter *adap)
{
	u32 needed_funcs = I2C_FUNC_SMBUS_BYTE | I2C_FUNC_SMBUS_WRITE_BYTE_DATA;

	/*
	 * If we ever want support for hardware doing SCCB natively, we will
	 * introduce a sccb_xfer() callback to struct i2c_algorithm and check
	 * for it here.
	 */

	return (i2c_get_functionality(adap) & needed_funcs) == needed_funcs;
}