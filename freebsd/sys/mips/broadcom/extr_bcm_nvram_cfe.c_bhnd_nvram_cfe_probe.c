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
struct bcm_platform {int /*<<< orphan*/ * nvram_cls; int /*<<< orphan*/ * nvram_io; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_NOWILDCARD ; 
 int ENXIO ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 struct bcm_platform* bcm_get_platform () ; 
 int /*<<< orphan*/  bhnd_nvram_data_class_desc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bhnd_nvram_cfe_probe(device_t dev)
{
	struct bcm_platform *bp;

	/* Fetch platform NVRAM I/O context */
	bp = bcm_get_platform();
	if (bp->nvram_io == NULL)
		return (ENXIO);

	KASSERT(bp->nvram_cls != NULL, ("missing NVRAM class"));

	/* Set the device description */
	device_set_desc(dev, bhnd_nvram_data_class_desc(bp->nvram_cls));

	/* Refuse wildcard attachments */
	return (BUS_PROBE_NOWILDCARD);
}