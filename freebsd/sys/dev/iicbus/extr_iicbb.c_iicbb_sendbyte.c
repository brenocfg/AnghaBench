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
typedef  int u_char ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_DEBUG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iicbb_one (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iicbb_zero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static void
iicbb_sendbyte(device_t dev, u_char data, int timeout)
{
	int i;

	for (i=7; i>=0; i--) {
		if (data&(1<<i)) {
			iicbb_one(dev, timeout);
		} else {
			iicbb_zero(dev, timeout);
		}
	}
	I2C_DEBUG(printf("w%02x",(int)data));
	return;
}