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
 int /*<<< orphan*/  SFF_8436_DATE_START ; 
 int /*<<< orphan*/  convert_sff_date (char*,size_t,char*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  read_i2c (struct i2c_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
get_qsfp_vendor_date(struct i2c_info *ii, char *buf, size_t size)
{
	char xbuf[6];

	memset(xbuf, 0, sizeof(xbuf));
	read_i2c(ii, SFF_8436_BASE, SFF_8436_DATE_START, 6, (uint8_t *)xbuf);
	convert_sff_date(buf, size, xbuf);
}