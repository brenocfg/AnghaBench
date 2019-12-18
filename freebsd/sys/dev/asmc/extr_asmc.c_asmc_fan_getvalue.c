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
typedef  int /*<<< orphan*/  fankey ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ asmc_key_read (int /*<<< orphan*/ ,char*,int*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char const*,int) ; 

__attribute__((used)) static int
asmc_fan_getvalue(device_t dev, const char *key, int fan)
{
	int speed;
	uint8_t buf[2];
	char fankey[5];

	snprintf(fankey, sizeof(fankey), key, fan);
	if (asmc_key_read(dev, fankey, buf, sizeof buf) < 0)
		return (-1);
	speed = (buf[0] << 6) | (buf[1] >> 2);

	return (speed);
}