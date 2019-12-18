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
struct TYPE_2__ {int /*<<< orphan*/  d_name; } ;
struct tuntap_driver {TYPE_1__ cdevsw; } ;
struct ifnet {int /*<<< orphan*/  if_dname; } ;

/* Variables and functions */
 int nitems (struct tuntap_driver*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tuntap_driver* tuntap_drivers ; 

__attribute__((used)) static struct tuntap_driver *
tuntap_driver_from_ifnet(const struct ifnet *ifp)
{
	struct tuntap_driver *drv;
	int i;

	if (ifp == NULL)
		return (NULL);

	for (i = 0; i < nitems(tuntap_drivers); ++i) {
		drv = &tuntap_drivers[i];
		if (strcmp(ifp->if_dname, drv->cdevsw.d_name) == 0)
			return (drv);
	}

	return (NULL);
}