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
struct linux_device_handler {scalar_t__ linux_major; } ;
struct device_element {int /*<<< orphan*/  entry; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  M_LINUX ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct device_element*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (struct linux_device_handler*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  devices ; 
 int /*<<< orphan*/  linux_major_starting ; 
 int /*<<< orphan*/  list ; 
 struct device_element* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
linux_device_register_handler(struct linux_device_handler *d)
{
	struct device_element *de;

	if (d == NULL)
		return (EINVAL);

	de = malloc(sizeof(*de), M_LINUX, M_WAITOK);
	if (d->linux_major < 0) {
		d->linux_major = linux_major_starting++;
	}
	bcopy(d, &de->entry, sizeof(*d));

	/* Add the element to the list, sorted on span. */
	TAILQ_INSERT_TAIL(&devices, de, list);

	return (0);
}