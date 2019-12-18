#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * device_t ;
struct TYPE_2__ {int cc_flags; int /*<<< orphan*/ * cc_dev; } ;

/* Variables and functions */
 int CRYPTOCAP_F_CLEANUP ; 
 int /*<<< orphan*/  CRYPTO_DRIVER_LOCK () ; 
 int /*<<< orphan*/  CRYPTO_DRIVER_UNLOCK () ; 
 TYPE_1__* crypto_drivers ; 
 int crypto_drivers_num ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ *) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,int) ; 

int
crypto_find_driver(const char *match)
{
	int i, len = strlen(match);

	CRYPTO_DRIVER_LOCK();
	for (i = 0; i < crypto_drivers_num; i++) {
		device_t dev = crypto_drivers[i].cc_dev;
		if (dev == NULL ||
		    (crypto_drivers[i].cc_flags & CRYPTOCAP_F_CLEANUP))
			continue;
		if (strncmp(match, device_get_nameunit(dev), len) == 0 ||
		    strncmp(match, device_get_name(dev), len) == 0)
			break;
	}
	CRYPTO_DRIVER_UNLOCK();
	return i < crypto_drivers_num ? i : -1;
}