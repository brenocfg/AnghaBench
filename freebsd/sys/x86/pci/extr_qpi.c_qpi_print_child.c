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
struct qpi_device {int qd_pcibus; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ bus_print_child_footer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_print_child_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct qpi_device* device_get_ivars (int /*<<< orphan*/ ) ; 
 scalar_t__ printf (char*,int) ; 

__attribute__((used)) static int
qpi_print_child(device_t bus, device_t child)
{
	struct qpi_device *qdev;
	int retval = 0;

	qdev = device_get_ivars(child);
	retval += bus_print_child_header(bus, child);
	if (qdev->qd_pcibus != -1)
		retval += printf(" pcibus %d", qdev->qd_pcibus);
	retval += bus_print_child_footer(bus, child);

	return (retval);
}