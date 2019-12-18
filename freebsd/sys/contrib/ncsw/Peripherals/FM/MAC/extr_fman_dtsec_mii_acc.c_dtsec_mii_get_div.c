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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;

/* Variables and functions */

__attribute__((used)) static uint8_t dtsec_mii_get_div(uint16_t dtsec_freq)
{
	uint16_t mgmt_clk;

	if (dtsec_freq < 80) mgmt_clk = 1;
	else if (dtsec_freq < 120) mgmt_clk = 2;
	else if (dtsec_freq < 160) mgmt_clk = 3;
	else if (dtsec_freq < 200) mgmt_clk = 4;
	else if (dtsec_freq < 280) mgmt_clk = 5;
	else if (dtsec_freq < 400) mgmt_clk = 6;
	else mgmt_clk = 7;

	return (uint8_t)mgmt_clk;
}