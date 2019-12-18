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
struct bhnd_resource {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bus_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_BUS_BARRIER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bhnd_resource*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void 
bhnd_barrier(device_t dev, device_t child, struct bhnd_resource *r,
    bus_size_t offset, bus_size_t length, int flags)
{
	BHND_BUS_BARRIER(device_get_parent(dev), child, r, offset, length,
	    flags);
}