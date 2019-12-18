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
typedef  int uint8_t ;
struct i2c_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SFF_8436_BASE ; 
 int /*<<< orphan*/  SFF_8436_TEMP ; 
 int /*<<< orphan*/  convert_sff_temp (char*,size_t,int*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  read_i2c (struct i2c_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static int
get_qsfp_temp(struct i2c_info *ii, char *buf, size_t size)
{
	uint8_t xbuf[2];

	memset(xbuf, 0, sizeof(xbuf));
	read_i2c(ii, SFF_8436_BASE, SFF_8436_TEMP, 2, xbuf);
	if ((xbuf[0] == 0xFF && xbuf[1] == 0xFF) || (xbuf[0] == 0 && xbuf[1] == 0))
		return (-1);
	convert_sff_temp(buf, size, xbuf);
	return (0);
}