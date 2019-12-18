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
struct viawd_device {int /*<<< orphan*/  desc; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_GENERIC ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct viawd_device* viawd_find (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
viawd_probe(device_t dev)
{
	struct viawd_device *id;

	id = viawd_find(device_get_parent(dev));
	KASSERT(id != NULL, ("parent should be a valid VIA SB"));
	device_set_desc(dev, id->desc);
	return (BUS_PROBE_GENERIC);
}