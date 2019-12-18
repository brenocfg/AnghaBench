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
struct isa_device {void* id_config_arg; int /*<<< orphan*/ * id_config_cb; } ;
typedef  int /*<<< orphan*/  isa_config_cb ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct isa_device* DEVTOISA (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
isa_set_config_callback(device_t dev, device_t child, isa_config_cb *fn,
    void *arg)
{
	struct isa_device* idev = DEVTOISA(child);

	idev->id_config_cb = fn;
	idev->id_config_arg = arg;
}