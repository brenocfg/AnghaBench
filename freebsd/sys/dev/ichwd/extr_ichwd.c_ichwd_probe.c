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
struct ichwd_device {int /*<<< orphan*/  desc; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ichwd_find_ich_lpc_bridge (int /*<<< orphan*/ ,struct ichwd_device**) ; 
 int /*<<< orphan*/ * ichwd_find_smb_dev (int /*<<< orphan*/ ,struct ichwd_device**) ; 
 scalar_t__ isa_get_logicalid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ichwd_probe(device_t dev)
{
	struct ichwd_device *id_p;

	/* Do not claim some ISA PnP device by accident. */
	if (isa_get_logicalid(dev) != 0)
		return (ENXIO);

	if (ichwd_find_ich_lpc_bridge(device_get_parent(dev), &id_p) == NULL &&
	    ichwd_find_smb_dev(device_get_parent(dev), &id_p) == NULL)
		return (ENXIO);

	device_set_desc_copy(dev, id_p->desc);
	return (0);
}