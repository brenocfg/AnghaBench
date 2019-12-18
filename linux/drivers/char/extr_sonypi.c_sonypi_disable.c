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
struct TYPE_2__ {int model; } ;

/* Variables and functions */
 int /*<<< orphan*/  SONYPI_ACPI_ACTIVE ; 
#define  SONYPI_DEVICE_MODEL_TYPE1 130 
#define  SONYPI_DEVICE_MODEL_TYPE2 129 
#define  SONYPI_DEVICE_MODEL_TYPE3 128 
 scalar_t__ camera ; 
 scalar_t__ fnkeyinit ; 
 int /*<<< orphan*/  outb (int,int) ; 
 int /*<<< orphan*/  sonypi_call2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sonypi_camera_off () ; 
 TYPE_1__ sonypi_device ; 
 int /*<<< orphan*/  sonypi_type1_dis () ; 
 int /*<<< orphan*/  sonypi_type2_dis () ; 
 int /*<<< orphan*/  sonypi_type3_dis () ; 

__attribute__((used)) static int sonypi_disable(void)
{
	sonypi_call2(0x81, 0);	/* make sure we don't get any more events */
	if (camera)
		sonypi_camera_off();

	/* disable ACPI mode */
	if (!SONYPI_ACPI_ACTIVE && fnkeyinit)
		outb(0xf1, 0xb2);

	switch (sonypi_device.model) {
	case SONYPI_DEVICE_MODEL_TYPE1:
		sonypi_type1_dis();
		break;
	case SONYPI_DEVICE_MODEL_TYPE2:
		sonypi_type2_dis();
		break;
	case SONYPI_DEVICE_MODEL_TYPE3:
		sonypi_type3_dis();
		break;
	}

	return 0;
}