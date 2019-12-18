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
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int bus_release_resource (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct resource*) ; 
 int /*<<< orphan*/  rman_get_rid (struct resource*) ; 

int
bus_free_resource(device_t dev, int type, struct resource *r)
{
	if (r == NULL)
		return (0);
	return (bus_release_resource(dev, type, rman_get_rid(r), r));
}