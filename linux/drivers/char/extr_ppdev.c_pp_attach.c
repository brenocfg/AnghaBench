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
struct parport {size_t number; int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct device*) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  PP_MAJOR ; 
 struct device* device_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,size_t) ; 
 struct device** devices ; 
 int /*<<< orphan*/  ppdev_class ; 
 int /*<<< orphan*/  pr_err (char*,size_t) ; 

__attribute__((used)) static void pp_attach(struct parport *port)
{
	struct device *ret;

	if (devices[port->number])
		return;

	ret = device_create(ppdev_class, port->dev,
			    MKDEV(PP_MAJOR, port->number), NULL,
			    "parport%d", port->number);
	if (IS_ERR(ret)) {
		pr_err("Failed to create device parport%d\n",
		       port->number);
		return;
	}
	devices[port->number] = ret;
}