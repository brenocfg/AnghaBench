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
typedef  int /*<<< orphan*/  xbuf ;
typedef  int /*<<< orphan*/  uint8_t ;
struct i2c_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SFF_8436_BASE ; 
 scalar_t__ SFF_8436_RX_CH1_MSB ; 
 int /*<<< orphan*/  convert_sff_power (struct i2c_info*,char*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  read_i2c (struct i2c_info*,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
get_qsfp_rx_power(struct i2c_info *ii, char *buf, size_t size, int chan)
{
	uint8_t xbuf[2];

	memset(xbuf, 0, sizeof(xbuf));
	read_i2c(ii, SFF_8436_BASE, SFF_8436_RX_CH1_MSB + (chan-1)*2, 2, xbuf);
	convert_sff_power(ii, buf, size, xbuf);
}