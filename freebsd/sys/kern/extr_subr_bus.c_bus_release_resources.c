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
struct resource_spec {int type; int /*<<< orphan*/  rid; } ;
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct resource*) ; 

void
bus_release_resources(device_t dev, const struct resource_spec *rs,
    struct resource **res)
{
	int i;

	for (i = 0; rs[i].type != -1; i++)
		if (res[i] != NULL) {
			bus_release_resource(
			    dev, rs[i].type, rs[i].rid, res[i]);
			res[i] = NULL;
		}
}