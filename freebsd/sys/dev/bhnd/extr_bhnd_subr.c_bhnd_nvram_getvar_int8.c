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
typedef  int /*<<< orphan*/  int8_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int bhnd_nvram_getvar_int (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int) ; 

int
bhnd_nvram_getvar_int8(device_t dev, const char *name, int8_t *value)
{
	return (bhnd_nvram_getvar_int(dev, name, value, sizeof(*value)));
}