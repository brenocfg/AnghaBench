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
 int BUS_DEACTIVATE_RESOURCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct resource*) ; 
 int /*<<< orphan*/  cbb_cardbus_auto_open (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cbb_cardbus_deactivate_resource(device_t brdev, device_t child, int type,
    int rid, struct resource *res)
{
	int ret;

	ret = BUS_DEACTIVATE_RESOURCE(device_get_parent(brdev), child,
	    type, rid, res);
	if (ret != 0)
		return (ret);
	cbb_cardbus_auto_open(device_get_softc(brdev), type);
	return (0);
}