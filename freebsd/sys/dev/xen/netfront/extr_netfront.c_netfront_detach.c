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
struct netfront_info {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*,int /*<<< orphan*/ ) ; 
 struct netfront_info* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_free (struct netfront_info*) ; 
 int /*<<< orphan*/  xenbus_get_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
netfront_detach(device_t dev)
{
	struct netfront_info *info = device_get_softc(dev);

	DPRINTK("%s\n", xenbus_get_node(dev));

	netif_free(info);

	return 0;
}