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
struct TYPE_2__ {scalar_t__ camera_power; } ;

/* Variables and functions */
 int /*<<< orphan*/  SONYPI_CAMERA_MUTE_MASK ; 
 int /*<<< orphan*/  SONYPI_CAMERA_PICTURE ; 
 int /*<<< orphan*/  sonypi_call2 (int,int /*<<< orphan*/ ) ; 
 TYPE_1__ sonypi_device ; 
 int /*<<< orphan*/  sonypi_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sonypi_camera_off(void)
{
	sonypi_set(SONYPI_CAMERA_PICTURE, SONYPI_CAMERA_MUTE_MASK);

	if (!sonypi_device.camera_power)
		return;

	sonypi_call2(0x91, 0);
	sonypi_device.camera_power = 0;
}