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
struct bhnd_chipid {scalar_t__ chip_type; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct bhnd_chipid* BHNDB_GET_CHIPID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ BHND_CHIPTYPE_BCMA ; 
 int ENXIO ; 
 int bcma_probe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bhnd_set_default_bus_desc (int /*<<< orphan*/ ,struct bhnd_chipid const*) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bcma_bhndb_probe(device_t dev)
{
	const struct bhnd_chipid	*cid;
	int				 error;

	/* Defer to default probe implementation */
	if ((error = bcma_probe(dev)) > 0)
		return (error);

	/* Check bus type */
	cid = BHNDB_GET_CHIPID(device_get_parent(dev), dev);
	if (cid->chip_type != BHND_CHIPTYPE_BCMA)
		return (ENXIO);

	/* Set device description */
	bhnd_set_default_bus_desc(dev, cid);

	return (error);
}