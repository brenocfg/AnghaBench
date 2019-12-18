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
struct gio_driver {int (* probe ) (struct gio_device*,struct gio_device_id const*) ;int /*<<< orphan*/  id_table; } ;
struct gio_device_id {int dummy; } ;
struct gio_device {int dummy; } ;
struct device {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  gio_dev_get (struct gio_device*) ; 
 int /*<<< orphan*/  gio_dev_put (struct gio_device*) ; 
 struct gio_device_id* gio_match_device (int /*<<< orphan*/ ,struct gio_device*) ; 
 int stub1 (struct gio_device*,struct gio_device_id const*) ; 
 struct gio_device* to_gio_device (struct device*) ; 
 struct gio_driver* to_gio_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gio_device_probe(struct device *dev)
{
	int error = -ENODEV;
	struct gio_driver *drv;
	struct gio_device *gio_dev;
	const struct gio_device_id *match;

	drv = to_gio_driver(dev->driver);
	gio_dev = to_gio_device(dev);

	if (!drv->probe)
		return error;

	gio_dev_get(gio_dev);

	match = gio_match_device(drv->id_table, gio_dev);
	if (match)
		error = drv->probe(gio_dev, match);
	if (error)
		gio_dev_put(gio_dev);

	return error;
}