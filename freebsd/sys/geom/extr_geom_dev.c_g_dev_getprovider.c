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
struct g_provider {int dummy; } ;
struct g_consumer {struct g_provider* provider; } ;
struct cdev {struct g_consumer* si_drv2; int /*<<< orphan*/ * si_devsw; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_dev_cdevsw ; 
 int /*<<< orphan*/  g_topology_assert () ; 

struct g_provider *
g_dev_getprovider(struct cdev *dev)
{
	struct g_consumer *cp;

	g_topology_assert();
	if (dev == NULL)
		return (NULL);
	if (dev->si_devsw != &g_dev_cdevsw)
		return (NULL);
	cp = dev->si_drv2;
	return (cp->provider);
}