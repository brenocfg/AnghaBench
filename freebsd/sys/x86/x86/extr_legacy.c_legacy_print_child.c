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
struct legacy_device {int lg_pcibus; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct legacy_device* DEVTOAT (int /*<<< orphan*/ ) ; 
 scalar_t__ bus_print_child_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ printf (char*,...) ; 

__attribute__((used)) static int
legacy_print_child(device_t bus, device_t child)
{
	struct legacy_device *atdev = DEVTOAT(child);
	int retval = 0;

	retval += bus_print_child_header(bus, child);
	if (atdev->lg_pcibus != -1)
		retval += printf(" pcibus %d", atdev->lg_pcibus);
	retval += printf("\n");

	return (retval);
}