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

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int E1000_I2C_DATA_IN ; 

__attribute__((used)) static bool e1000_get_i2c_data(u32 *i2cctl)
{
	bool data;

	DEBUGFUNC("e1000_get_i2c_data");

	if (*i2cctl & E1000_I2C_DATA_IN)
		data = 1;
	else
		data = 0;

	return data;
}