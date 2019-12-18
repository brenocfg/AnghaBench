#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int count; int /*<<< orphan*/ * elements; } ;
union acpi_object {scalar_t__ type; TYPE_1__ package; } ;
struct acpi_fan_fps {int dummy; } ;
struct acpi_fan {int fps_count; char* fps; } ;
struct acpi_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  handle; } ;
struct acpi_buffer {int member_0; char* member_1; union acpi_object* pointer; } ;
typedef  int acpi_status ;

/* Variables and functions */
 int ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_FAILURE (int) ; 
 scalar_t__ ACPI_TYPE_PACKAGE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct acpi_fan* acpi_driver_data (struct acpi_device*) ; 
 int acpi_evaluate_object (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,struct acpi_buffer*) ; 
 int acpi_extract_package (int /*<<< orphan*/ *,struct acpi_buffer*,struct acpi_buffer*) ; 
 int /*<<< orphan*/  acpi_fan_speed_cmp ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 char* devm_kcalloc (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (union acpi_object*) ; 
 int /*<<< orphan*/  sort (char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int acpi_fan_get_fps(struct acpi_device *device)
{
	struct acpi_fan *fan = acpi_driver_data(device);
	struct acpi_buffer buffer = { ACPI_ALLOCATE_BUFFER, NULL };
	union acpi_object *obj;
	acpi_status status;
	int i;

	status = acpi_evaluate_object(device->handle, "_FPS", NULL, &buffer);
	if (ACPI_FAILURE(status))
		return status;

	obj = buffer.pointer;
	if (!obj || obj->type != ACPI_TYPE_PACKAGE || obj->package.count < 2) {
		dev_err(&device->dev, "Invalid _FPS data\n");
		status = -EINVAL;
		goto err;
	}

	fan->fps_count = obj->package.count - 1; /* minus revision field */
	fan->fps = devm_kcalloc(&device->dev,
				fan->fps_count, sizeof(struct acpi_fan_fps),
				GFP_KERNEL);
	if (!fan->fps) {
		dev_err(&device->dev, "Not enough memory\n");
		status = -ENOMEM;
		goto err;
	}
	for (i = 0; i < fan->fps_count; i++) {
		struct acpi_buffer format = { sizeof("NNNNN"), "NNNNN" };
		struct acpi_buffer fps = { sizeof(fan->fps[i]), &fan->fps[i] };
		status = acpi_extract_package(&obj->package.elements[i + 1],
					      &format, &fps);
		if (ACPI_FAILURE(status)) {
			dev_err(&device->dev, "Invalid _FPS element\n");
			break;
		}
	}

	/* sort the state array according to fan speed in increase order */
	sort(fan->fps, fan->fps_count, sizeof(*fan->fps),
	     acpi_fan_speed_cmp, NULL);

err:
	kfree(obj);
	return status;
}