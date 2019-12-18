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
struct dio_driver {int (* probe ) (struct dio_dev*,struct dio_device_id const*) ;int /*<<< orphan*/  id_table; } ;
struct dio_device_id {int dummy; } ;
struct dio_dev {struct dio_driver* driver; } ;
struct device {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 struct dio_device_id* dio_match_device (int /*<<< orphan*/ ,struct dio_dev*) ; 
 int stub1 (struct dio_dev*,struct dio_device_id const*) ; 
 struct dio_dev* to_dio_dev (struct device*) ; 
 struct dio_driver* to_dio_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dio_device_probe(struct device *dev)
{
	int error = 0;
	struct dio_driver *drv = to_dio_driver(dev->driver);
	struct dio_dev *d = to_dio_dev(dev);

	if (!d->driver && drv->probe) {
		const struct dio_device_id *id;

		id = dio_match_device(drv->id_table, d);
		if (id)
			error = drv->probe(d, id);
		if (error >= 0) {
			d->driver = drv;
			error = 0;
		}
	}
	return error;
}