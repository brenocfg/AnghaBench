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
typedef  char uint8_t ;
typedef  int /*<<< orphan*/  fankey ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ asmc_key_read (int /*<<< orphan*/ ,char*,char*,char) ; 
 int /*<<< orphan*/  snprintf (char*,int,char const*,int) ; 

__attribute__((used)) static char*
asmc_fan_getstring(device_t dev, const char *key, int fan, uint8_t *buf, uint8_t buflen)
{
	char fankey[5];
	char* desc;

	snprintf(fankey, sizeof(fankey), key, fan);
	if (asmc_key_read(dev, fankey, buf, buflen) < 0)
		return (NULL);
	desc = buf+4;

	return (desc);
}