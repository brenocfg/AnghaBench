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
 struct resource* CIS_CONFIG_SPACE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_delete_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct resource*) ; 

__attribute__((used)) static void
cardbus_read_tuple_finish(device_t cbdev, device_t child, int rid,
    struct resource *res)
{
	if (res != CIS_CONFIG_SPACE) {
		bus_release_resource(child, SYS_RES_MEMORY, rid, res);
		bus_delete_resource(child, SYS_RES_MEMORY, rid);
	}
}