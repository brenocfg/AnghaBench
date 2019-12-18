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
struct vr_type {int /*<<< orphan*/  vr_name; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vr_type* vr_match (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vr_probe(device_t dev)
{
	const struct vr_type	*t;

	t = vr_match(dev);
	if (t != NULL) {
		device_set_desc(dev, t->vr_name);
		return (BUS_PROBE_DEFAULT);
	}
	return (ENXIO);
}