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
typedef  int u8 ;
struct si5351_parameters {int p1; int p2; int p3; int valid; } ;
struct si5351_driver_data {int dummy; } ;

/* Variables and functions */
#define  SI5351_CLK6_PARAMETERS 129 
#define  SI5351_CLK7_PARAMETERS 128 
 int SI5351_PARAMETERS_LENGTH ; 
 int /*<<< orphan*/  si5351_bulk_read (struct si5351_driver_data*,int,int,int*) ; 
 int si5351_reg_read (struct si5351_driver_data*,int) ; 

__attribute__((used)) static void si5351_read_parameters(struct si5351_driver_data *drvdata,
				   u8 reg, struct si5351_parameters *params)
{
	u8 buf[SI5351_PARAMETERS_LENGTH];

	switch (reg) {
	case SI5351_CLK6_PARAMETERS:
	case SI5351_CLK7_PARAMETERS:
		buf[0] = si5351_reg_read(drvdata, reg);
		params->p1 = buf[0];
		params->p2 = 0;
		params->p3 = 1;
		break;
	default:
		si5351_bulk_read(drvdata, reg, SI5351_PARAMETERS_LENGTH, buf);
		params->p1 = ((buf[2] & 0x03) << 16) | (buf[3] << 8) | buf[4];
		params->p2 = ((buf[5] & 0x0f) << 16) | (buf[6] << 8) | buf[7];
		params->p3 = ((buf[5] & 0xf0) << 12) | (buf[0] << 8) | buf[1];
	}
	params->valid = 1;
}