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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct i2c_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SFF_8436_BASE ; 
 int /*<<< orphan*/  SFF_8436_BITRATE ; 
 int /*<<< orphan*/  SFF_8636_BITRATE ; 
 int /*<<< orphan*/  read_i2c (struct i2c_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static uint32_t 
get_qsfp_br(struct i2c_info *ii)
{
	uint8_t xbuf;
	uint32_t rate;

	xbuf = 0;
	read_i2c(ii, SFF_8436_BASE, SFF_8436_BITRATE, 1, &xbuf);
	rate = xbuf * 100;
	if (xbuf == 0xFF) {
		read_i2c(ii, SFF_8436_BASE, SFF_8636_BITRATE, 1, &xbuf);
		rate = xbuf * 250;
	}

	return (rate);
}