#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_6__ {TYPE_1__* str_obj; } ;
struct acpi_device {TYPE_3__ pnp; } ;
typedef  int ssize_t ;
struct TYPE_5__ {int /*<<< orphan*/  length; scalar_t__ pointer; } ;
struct TYPE_4__ {TYPE_2__ buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  UTF16_LITTLE_ENDIAN ; 
 struct acpi_device* to_acpi_device (struct device*) ; 
 int utf16s_to_utf8s (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t description_show(struct device *dev,
				struct device_attribute *attr,
				char *buf) {
	struct acpi_device *acpi_dev = to_acpi_device(dev);
	int result;

	if (acpi_dev->pnp.str_obj == NULL)
		return 0;

	/*
	 * The _STR object contains a Unicode identifier for a device.
	 * We need to convert to utf-8 so it can be displayed.
	 */
	result = utf16s_to_utf8s(
		(wchar_t *)acpi_dev->pnp.str_obj->buffer.pointer,
		acpi_dev->pnp.str_obj->buffer.length,
		UTF16_LITTLE_ENDIAN, buf,
		PAGE_SIZE);

	buf[result++] = '\n';

	return result;
}