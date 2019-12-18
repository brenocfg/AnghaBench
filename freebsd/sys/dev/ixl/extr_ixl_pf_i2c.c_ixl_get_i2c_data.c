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
struct ixl_pf {int dummy; } ;

/* Variables and functions */
 int I40E_GLGEN_I2CPARAMS_DATA_IN_MASK ; 

__attribute__((used)) static bool
ixl_get_i2c_data(struct ixl_pf *pf, u32 *i2cctl)
{
	bool data;

	if (*i2cctl & I40E_GLGEN_I2CPARAMS_DATA_IN_MASK)
		data = 1;
	else
		data = 0;

	return data;
}